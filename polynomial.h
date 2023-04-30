#ifndef PO_POLYNOMIAL_H
#define PO_POLYNOMIAL_H

#include "types/rank.h"
#include "types/degree.h"

#include "evaluate/evaluate.h"
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
#include <atomic>

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
    /*
     * Counts ctor invocations
     */
    static std::uint64_t construction_count()
    {
      return m_construction_count.load();
    }

    model::storage terms;

  private:
    static std::atomic<std::uint64_t> m_construction_count;

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
     * Make a constant polynomial of the given rank. The resulting
     * polynomial has one term.
     *
     */
    static polynomial make_constant(rank_type rank, scalar_type constant)
    {
      return polynomial(rank, constant);
    }

  private:
    polynomial(rank_type rank, const scalar_type& c):
      polynomial(rank)
    {
      accumulate_add(terms, c, exponents(exponent_type{0}, rank));
    }

    polynomial(rank_type rank):
      terms{},
      m_degree{0},
      m_degrees(degree_type{0}, rank),
      m_rank{rank}
    {
      ++m_construction_count;
    }

  public:
#if 0
    // Disabled
    /*
     * Construct a zero polynomial with the given rank. The resulting
     * polynomial has empty storage.
     */
    template<rank_type R>
    polynomial(rank<R>&&):
      polynomial(R)
    {
      ++m_construction_count;
    }
#endif
    /*
     * Construct a polynomial from a supported expression type instance.
     */
    template<expression Expr>
    polynomial(Expr&& expr):
      polynomial(instantiate(expr))
    {
      ++m_construction_count;
    }


    /*
     * Construct a polynomial from an r-value `std::initializer_list` of tuples.
     * This typically begins with a "braced-init-list" (which is not a std::initializer_list).
     *
     * polynomial p({0.2, {4, 3, 5, 7}});
     * polynomial p{{0.2, {4, 3, 5, 7}}};
     * polynomial p({{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}});
     * polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
     */
    polynomial(
      std::initializer_list
        <
          std::tuple<scalar_type, std::initializer_list<exponent_type>>
        >
        && _ilist)
    : terms{},
      m_degree{0},
      m_degrees(
        _ilist.size() > 0
        ? std::get<1>(*_ilist.begin())
        : std::valarray<std::size_t>()),
      m_rank{
        _ilist.size() > 0
        ? std::get<1>(*_ilist.begin()).size()
        : 0}
    {
      ++m_construction_count;
      for(auto&& t : _ilist)
      {
        m_degree = std::max(m_degree, std::accumulate(std::get<1>(t).begin(), std::get<1>(t).end(), degree_type{0}));
        std::size_t i = 0;
        for(auto&& x : std::get<1>(t))
        {
          m_degrees[i] = std::max(m_degrees[i], degree_type{x});
          ++i;
        }

        terms.emplace_back(std::move(std::get<0>(t)), std::move(std::get<1>(t)));
      }
    }

#if 0
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
#endif
    /*
     * Instantiate an expression and assign it. E.g.,
     * p = 3*p - q*(-4*r + q*q);
     */
    template<expression Expr>
    polynomial& operator=(Expr expr);

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
      return model::get_constant(terms);
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
      using S = std::common_type_t<scalar_type, X...>;

      // TODO Remove branch, shouldn't be necessary
      if (sizeof ...(x) != rank())
        return nan;
      else
        return evaluate(*this, S(x)...);
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
#include "ops/expr_antiderivative.h"

#include "ops/instantiate.h"

namespace po
{
  template<expression Expr>
  polynomial& polynomial::operator=(Expr expr)
  {
    if constexpr(is_constant<Expr>)
    {
      terms.clear();
      m_degrees.resize(0);
      m_degree = 0;
      m_rank = 0;
      if constexpr(is_scalar<Expr>)
      {
        return (*this += expr);
      }
      else
      {
        return (*this += expr.expr1);
      }
    }

    if constexpr(is_polynomial<Expr>)
    {
      terms = expr.terms;
      m_degrees = expr.m_degrees;
      m_degree = expr.m_degree;
      m_rank = expr.m_rank;
      return *this;
    }

    return (*this = instantiate(expr));
  }

  template<typename E>
  concept is_expr_binary_plus =
    is_binary_expression<E> &&
    std::same_as<E, expr_binary_plus<typename E::_E1, typename E::_E2>>;

  template<expression Expr>
  polynomial& operator+=(polynomial& p, Expr&& expr)
  {
    if constexpr(is_constant<Expr>)
    {
      return p.operator+=(expr.expr1);
    }

    if constexpr(is_polynomial<Expr>)
    {
      return p.operator+=(expr);
    }

    if constexpr(is_expr_binary_plus<Expr>)
    {
      if constexpr(is_polynomial<typename Expr::_E1> && is_polynomial<typename Expr::_E2>)
      {
        if(&p != &expr.expr1 && &p != &expr.expr2)
        {
          return p.operator+=(expr.expr1).operator+=(expr.expr2);
        }

        if(&p == &expr.expr1 && &p != &expr.expr2)
        {
          return p.operator*=(2).operator+=(expr.expr2);
        }

        if(&p != &expr.expr1 && &p == &expr.expr2)
        {
          return p.operator*=(2).operator+=(expr.expr1);
        }

        if(&p == &expr.expr1 && &p == &expr.expr2)
        {
          return p.operator*=(3);
        }

      }
    }

    return p.operator+=(instantiate(expr));
  }

  template<expression Expr>
  polynomial& operator-=(polynomial& p, Expr&& expr)
  {
    if constexpr(is_constant<Expr>)
    {
      return p.operator-=(expr.expr1);
    }

    if constexpr(is_polynomial<Expr>)
    {
      return p.operator-=(expr);
    }

    return p.operator-=(instantiate(expr));
  }

  template<expression Expr>
  polynomial& operator*=(polynomial& p, Expr&& expr)
  {
    if constexpr(is_constant<Expr>)
    {
      return p.operator*=(expr.expr1);
    }

    if constexpr(is_polynomial<Expr>)
    {
      return p.operator*=(expr);
    }

    return p.operator*=(instantiate(expr));
  }

/*
  po::polynomial zero(rank_type rank)
  {
    return polynomial::make_zero(rank);
  }

  po::polynomial constant(scalar_type&& c, rank_type rank)
  {
    return polynomial::make_constant(rank, std::move(c));
  }
*/


  std::atomic<std::uint64_t> polynomial::m_construction_count{0};
}

#endif

