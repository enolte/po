#ifndef PO_POLYNOMIAL_H
#define PO_POLYNOMIAL_H

#include "types/rank.h"
#include "types/degree.h"

#include "evaluate.h"
#include "types/monomial.h"

#include "storage/flat.h"

#include "ops/expr_constant.h"
#include "ops/expr_unary_plus.h"
#include "ops/expr_unary_minus.h"
#include "ops/expr_binary_plus.h"
#include "ops/expr_binary_minus.h"
#include "ops/expr_binary_mult.h"

#include "ops/is_exponent.h"

#include <numeric>
#include <algorithm>

namespace po
{
  /*
   * Storage model for polynomial terms
   */
  namespace model = po::flat_model;

  /*
   * Multivariate polynomial type.
   *
   * Only additive representations are modeled.
   *
   */
  struct polynomial
  {
    model::storage terms;

  private:
    degree_type m_degree;

    exponents m_degrees;

    rank_type m_rank;

  public:
    constexpr void update_degrees()
    {
      m_degree = 0;

      for(auto i{0zu}; i < m_rank; ++i)
        m_degrees[i] = 0;

      std::ranges::for_each(
        terms,
        [this](const auto& t)
        {
          m_degree = std::max(m_degree, t.degree());
          for(auto i{0zu}; i < m_rank; ++i)
            m_degrees[i] = std::max(m_degrees[i], t.exponents[i]);
        });
    }

  public:

    /*
     * Make a zero polynomial of the given rank. The resulting
     * polynomial has empty storage.
     *
     */
    static polynomial make_zero(rank_type rank)
    {
      return polynomial(rank);
    }

    /*
     * Construct a zero polynomial of given rank. The resulting
     * polynomial has empty storage.
     */
    polynomial(rank_type rank):
      terms{},
      m_degree{0},
      m_degrees(degree_type{0}, rank),
      m_rank{rank}
    {}

    /*
     * Construct a constant polynomial of given rank. The resulting
     * polynomial has one term.
     *
     * polynomial p(2.12, rank<15>{});
     * polynomial p{2.12, 15};
     */
    polynomial(const scalar_type& c, rank_type rank):
      polynomial(rank)
    {
      accumulate_add(terms, c, exponents(exponent_type{0}, rank));
    }

    /*
     * Construct a polynomial from a supported expression type instance.
     */
    template<expression Expr>
    polynomial(Expr&& expr):
      polynomial(instantiate(expr))
    {}

    /*
     * Construct a polynomial from an r-value `std::initializer_list` of monomials.
     * This typically begins with a "braced-init-list" (which is not a std::initializer_list).
     *
     * polynomial p({0.2, {4, 3, 5, 7}});
     * polynomial p{{0.2, {4, 3, 5, 7}}};
     * polynomial p({{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}});
     * polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
     */
    polynomial(std::initializer_list<monomial>&& _ilist)
    : terms{std::forward<decltype(_ilist)>(_ilist)},
      m_degree{0},
      m_degrees(
        _ilist.size() > 0
        ? _ilist.begin()->exponents
        : std::valarray<std::size_t>()),
      m_rank{
        _ilist.size() > 0
        ? _ilist.begin()->rank()
        : 0}
    {
      for(const auto& t : terms)
      {
        m_degree = std::max(m_degree, t.degree());
/*
        // g++ 11.2: probable bug in std::valarray, causes seg fault here if the predicate is false for every
        // component, which produces a zero-length mask array, which is unchecked before assignment in
        // std::valarray ctor
        m_degrees[m_degrees < t.exponents] = t.exponents;
*/

        for(auto i{0zu}; i < t.rank(); ++i)
          m_degrees[i] = std::max(m_degrees[i], t.exponents[i]);
      }
    }

#if 0
    // Disabled for operator overload resolution
    /*
     * Construct from monomial fields
     *
     * polynomial p(2.17, {2, 3, 2, 1});
     * polynomial p{2.17, {2, 3, 2, 1}};
     */
    constexpr polynomial(scalar_type&& _coefficient, std::initializer_list<exponent_type>&& _exponents)
    : terms{{std::move(_coefficient), std::move(_exponents)}},
      m_degree{0},
      m_degrees{_exponents},
      m_rank{_exponents.size()}
    {
      for(const auto& t : terms)
        m_degree = std::max(m_degree, t.degree());
    }
#endif


#if 0
    // TODO Verify removal.
    polynomial(const polynomial&) = default;
    polynomial(polynomial&&) = default;

    polynomial& operator=(const polynomial&) = default;
    polynomial& operator=(polynomial&&) = default;
#endif

    /*
     * Instantiate and expression and assign it. E.g.,
     * p = 3*p - q*(-4*r + q*q);
     */
    template<expression Expr>
    polynomial& operator=(Expr&& expr);

    // TODO This function does not absorb the monomial.
    polynomial& operator=(monomial&& m)
    {
      zero();
      m_rank = m.rank();
      m_degrees.resize(m_rank);
      accumulate_add(terms, m.coefficient, m.exponents);
      update_degrees();
      return *this;
    }

    polynomial& operator=(const monomial& m)
    {
      zero();
      m_rank = m.rank();
      m_degrees.resize(m_rank);
      accumulate_add(terms, m.coefficient, m.exponents);
      update_degrees();
      return *this;
    }


    /*
     * Set this polynomial to be the zero polynomial.
     * This does not change this object's rank.
     */
    void zero()
    {
      terms.clear();
      m_degree = 0;
      m_degrees = 0;
    }

    /*
     * Get the maximum degree value of the ith variable which occurs in any monomial term.
     * This implies no consideration for coefficient values.
     *
     * TODO
     * Specifically, a term's exponents are accounted even if its coefficient value is zero or NaN.
     */
    degree_type degree(std::size_t i) const
    {
      if(rank() > i)
        return m_degrees[i];
      else
        return 0;
    }

    const std::valarray<degree_type>& degrees() const
    {
      return m_degrees;
    }

    /*
     * Get the total degree of this polynomial.
     */
    std::size_t degree() const
    {
      return m_degree;
    }

    /*
     * The rank of a polynomial is defined to the number of variables in the polynomial.
     */
    std::size_t rank() const
    {
      return m_rank;
    }

    /*
     * Get a copy of the constant term from this polynomial.
     */
    scalar_type constant() const
    {
      return model::constant(terms);
    }

    /*
     * Get number of additive terms in `this`@entry
     */
    std::size_t nterms() const
    {
      return model::nterms(terms);
    }

    /*
     * Evaluate this polynomial at the given args.
     *
     */
    template<scalar ...X>
    scalar_type operator()(X&&... x) const
    {
      using S = std::common_type_t<scalar_type, X&&...>;
      // return evaluate_naive(*this, S(x)...);
      return evaluate_gH(*this, S(x)...);
    }

    /*
     * Get the coefficient of the term with the given exponents.
     */
    scalar_type coefficient(const po::exponents& exponents) const
    {
      return find_coefficient(terms, exponents);
    }

    /*
     * Get the coefficient of the term with multiindex given by pack MI.
     */
    template<exponent ...MI>
    constexpr scalar_type coefficient(MI... mi) const
    {
      return find_coefficient(terms, mi...);
    }

    /*
     * Add a scalar constant.
     *
     * p += 6;
     * p += {6};
     */
    polynomial& operator+=(scalar_type c)
    {
      accumulate_add(terms, std::forward<scalar_type>(c), exponents(exponent_type{0}, rank()));

      return *this;
    }

    /*
     * Add a monomial term.
     */
    constexpr polynomial& operator+=(const monomial& t)
    {
      accumulate_add(terms, t.coefficient, t.exponents);
      update_degrees();

      return *this;
    }

    /*
     * Add a monomial term.
     *
     * p += {5.05, {3, 6}};
     */
    constexpr polynomial& operator+=(monomial&& t)
    {
      accumulate_add(terms, std::forward<scalar_type>(t.coefficient), std::forward<exponents>(t.exponents));
      update_degrees();

      return *this;
    }

    /*
     * Add an init-list of monomial terms.
     *
     * p += {5, {3, 4, 2, 0, 4, 5}};
     * p += {{5, {3, 4, 2, 0, 4, 5}}, {2.4, {0, 0, 2, 3, 4, 5}}};
     */
    constexpr polynomial& operator+=(std::initializer_list<monomial>&& t)
    {
      for(auto&& m : t)
        accumulate_add(terms, std::move(m.coefficient), std::move(m.exponents));

      update_degrees();

      return *this;
    }

    /*
     * Add a polynomial.
     *
     * p += std::move(q);
     */
    // TODO This function does not absorb the polynomial.
    polynomial& operator+=(polynomial&& q)
    {
      for(const auto& s : q.terms)
        accumulate_add(terms, s.coefficient, s.exponents);

      update_degrees();

      return *this;
    }

    /*
     * Add a polynomial.
     *
     * p += q;
     */
    polynomial& operator+=(const polynomial& q)
    {
      for(const auto& s : q.terms)
        accumulate_add(terms, s.coefficient, s.exponents);

      update_degrees();

      return *this;
    }

    /*
     * Subtract a polynomial.
     *
     * p -= std::move(q);
     */
    // TODO This function does not absorb the polynomial.
    // TODO test
    polynomial& operator-=(polynomial&& q)
    {
      for(const auto& s : q.terms)
        accumulate_add(terms, -s.coefficient, s.exponents);

      update_degrees();

      return *this;
    }

    /*
     * Subtract a polynomial.
     *
     * p -= q;
     */
    polynomial& operator-=(const polynomial& q)
    {
      for(const auto& s : q.terms)
        accumulate_add(terms, -s.coefficient, s.exponents);

      update_degrees();

      return *this;
    }

    /*
     * Subtract a scalar constant.
     *
     * p -= 6;
     * p -= {6};
     */
    polynomial& operator-=(scalar_type c)
    {
      accumulate_add(terms, std::forward<scalar_type>(-c), exponents(exponent_type{0}, rank()));

      return *this;
    }


    /*
     * Subtract a monomial term.
     *
     * p -= m;
     */
    constexpr polynomial& operator-=(const monomial& t)
    {
      accumulate_add(terms, -t.coefficient, t.exponents);
      update_degrees();

      return *this;
    }

    /*
     * Subtract a monomial term.
     *
     * p -= {5.05, {3, 6}};
     */
    constexpr polynomial& operator-=(monomial&& t)
    {
      accumulate_add(terms, -t.coefficient, std::forward<exponents>(t.exponents));
      update_degrees();

      return *this;
    }

    /*
     * Subtract an init-list of monomial terms.
     *
     * p -= {5, {3, 4, 2, 0, 4, 5}};
     * p -= {{5, {3, 4, 2, 0, 4, 5}}, {2.4, {0, 0, 2, 3, 4, 5}}};
     */
    constexpr polynomial& operator-=(std::initializer_list<monomial>&& monomials)
    {
      for(auto& t : monomials)
        accumulate_add(terms, -t.coefficient, std::move(t.exponents));
      update_degrees();

      return *this;
    }

    /*
     * Multiply by a scalar constant.
     *
     */
    polynomial& operator*=(scalar_type c)
    {
      accumulate_mult(terms, std::move(c));
      return *this;
    }

    /*
     * Multiply by rvalue monomial.
     *
     * p *= {5., {3, 2, 1, 2}};
     */
    // TODO This function does not absorb the monomial.
    polynomial& operator*=(monomial&& m)
    {
      accumulate_mult(terms, m.coefficient, m.exponents);
      update_degrees();

      return *this;
    }

    /*
     * Multiply by a monomial.
     */
    polynomial& operator*=(const monomial& m)
    {
      accumulate_mult(terms, m.coefficient, m.exponents);
      update_degrees();

      return *this;
    }

    /*
     * Multiply by another polynomial.
     */
    polynomial& operator*=(const polynomial& q)
    {
      accumulate_mult(terms, q.terms);
      update_degrees();

      return *this;
    }

    /*
     * Multiply by another polynomial.
     */
    // TODO This function does not absorb the polynomial.
    polynomial& operator*=(polynomial&& q)
    {
      accumulate_mult(terms, q.terms);
      update_degrees();

      return *this;
    }

    polynomial& operator*=(std::initializer_list<monomial>&& list)
    {
      accumulate_mult(terms, std::forward<std::initializer_list<monomial>>(list));
      update_degrees();

      return *this;
    }
  };

}

#include "ops/expr_partial_derivative.h"
#include "ops/expr_integral.h"

#include "ops/instantiate.h"

namespace po
{
  template<expression Expr>
  polynomial& polynomial::operator=(Expr&& expr)
  {
    return (*this = instantiate(expr));
  }

  template<expression Expr>
  polynomial& operator+=(polynomial& p, Expr&& expr)
  {
    return p.operator+=(instantiate(expr));
  }

  template<expression Expr>
  polynomial& operator-=(polynomial& p, Expr&& expr)
  {
    return p.operator-=(instantiate(expr));
  }

  template<expression Expr>
  polynomial& operator*=(polynomial& p, Expr&& expr)
  {
    return p.operator*=(instantiate(expr));
  }

}

#endif

