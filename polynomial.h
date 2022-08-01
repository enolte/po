#ifndef PO_POLYNOMIAL_H
#define PO_POLYNOMIAL_H

#include "rank.h"
#include "degree.h"

#include "evaluate.h"
#include "monomial.h"
#include "default_types.h"

#include "ops/find_coefficient.h"

#include "ops/add_eq_constant.h"
#include "ops/add_eq_monomial.h"
#include "ops/add_eq_polynomial.h"
#include "ops/sub_eq_monomial.h"
#include "ops/sub_eq_polynomial.h"
#include "ops/mult_eq_monomial.h"
#include "ops/mult_eq_scalar.h"
#include "ops/mult_eq_polynomial.h"
#include "ops/mult_eq_init_list.h"

#include "ops/expr_constant.h"
#include "ops/expr_unary_plus.h"
#include "ops/expr_unary_minus.h"
#include "ops/expr_binary_plus.h"
#include "ops/expr_binary_minus.h"
#include "ops/expr_binary_mult.h"

#include <vector>
#include <valarray>
#include <numeric>
#include <algorithm>


namespace po
{
  /*
   * Multivariate polynomial type.
   *
   * Only additive representations are modeled.
   *
   */
  struct polynomial
  {
    std::vector<monomial> terms;

    scalar_type constant_term;

    degree_type total_degree;

    std::valarray<degree_type> variable_degrees;

    rank_type this_rank;

    /*
     * Construct a constant polynomial of rank R.
     *
     * polynomial p(2.12, rank<15>{});
     * polynomial p{2.12, rank<15>{}};
     */
    template<std::size_t R>
    polynomial(scalar_type&& c, po::rank<R>&&):
      terms{},
      constant_term{0},
      total_degree{0},
      variable_degrees(index_data_type{0}, R),
      this_rank{R}
    {
      add_constant(std::move(c));
    }

    template<std::size_t R>
    polynomial(const scalar_type& c, po::rank<R>&&):
      terms{},
      constant_term{0},
      total_degree{0},
      variable_degrees(index_data_type{0}, R),
      this_rank{R}
    {
      add_constant(std::move(c));
    }

    // TODO
    /*
     * Construct a zero polynomial of rank R from a raw `rank_type`.
     * N.B.: This ctor is used only to evaluate partial derivative expressions. It should not be
     * directly used to construct a polynomial object. This ctor will be removed if/when the polynomial
     * type is converted to a type template with a rank parameter.
     *
     * polynomial p{15};
     */
    explicit polynomial(rank_type rank):
      terms{},
      constant_term{0},
      total_degree{0},
      variable_degrees(index_data_type{0}, rank),
      this_rank{rank}
    {}

    /*
     * Construct a zero polynomial of rank R.
     *
     * polynomial p{rank<15>{}};
     */
    template<std::size_t R>
    polynomial(po::rank<R>&&):
      terms{},
      constant_term{0},
      total_degree{0},
      variable_degrees(index_data_type{0}, R),
      this_rank{R}
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
      variable_degrees(
        _ilist.size() > 0
        ? _ilist.begin()->exponents
        : std::valarray<std::size_t>()),
      constant_term{scalar_type{0}},
      this_rank{
        _ilist.size() > 0
        ? _ilist.begin()->rank()
        : 0}
    {
      total_degree = index_data_type{0};
      for(auto&& t : terms)
      {
        if(t.degree() == 0)
          constant_term += t.coefficient;

        total_degree = std::max(total_degree, t.degree());

        for(auto i{0zu}; i < t.rank(); ++i)
          variable_degrees[i] = std::max(variable_degrees[i], t.exponents[i]);
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
    polynomial(scalar_type&& _coefficient, std::initializer_list<exponent_type>&& _exponents)
    : terms{{std::move(_coefficient), std::move(_exponents)}},
      variable_degrees{_exponents},
      constant_term{
          std::accumulate(std::cbegin(_exponents), std::cend(_exponents), 0) == 0
            ? std::move(_coefficient)
            : scalar_type(0)},
      this_rank{_exponents.size()}
    {}
#endif

    /*
     * Construct from a coefficient and an exponent pack, for construction from the fields
     * for a single monomial term.
     *
     * polynomial p(7.7, 3, 4, 5);
     * polynomial p{7.7, 3, 4, 5};
     * polynomial{7.7, 3, 4, 5};
     */
    template<typename Scalar, typename ...Exponents>
      requires is_scalar<Scalar> && (sizeof ...(Exponents) > 0) && (std::integral<Exponents> && ...)
    polynomial(Scalar&& _coefficient, Exponents&&... _exponents)
    : terms{{std::move(scalar_type(_coefficient)), {exponent_type(_exponents)...}}},
      variable_degrees{exponent_type(_exponents)...},
      constant_term{
        ((_exponents == exponent_type(0)) && ...)
          ? std::move(_coefficient)
          : scalar_type(0)},
      this_rank{sizeof ...(_exponents)}
    {}

    polynomial(const polynomial&) = default;
    polynomial(polynomial&&) = default;

    polynomial& operator=(const polynomial&) = default;
    polynomial& operator=(polynomial&&) = default;

    polynomial& operator=(scalar_type c)
    {
      zero();
      add_constant(c);
      return *this;
    }


    /*
     * Get the maximum degree value of the ith variable which occurs in any monomial term.
     * This implies no consideration for coefficient values.
     *
     * TODO
     * Specifically, a term's exponents are accounted even if its coefficient value is zero or NaN.
     */
    std::size_t degree(std::size_t i) const
    {
      if(rank() > i)
        return variable_degrees[i];
      else
        return 0;
    }

    /*
     * Get the total degree of this polynomial.
     */
    std::size_t degree() const
    {
      return this->total_degree;
    }

    /*
     * The rank of a polynomial is defined to the number of variables in the polynomial.
     */
    std::size_t rank() const
    {
      return this->this_rank;
    }

    /*
     * Get a copy of the constant term from this polynomial.
     */
    scalar_type constant() const
    {
      return this->constant_term;
    }

    /*
     * Get number of additive terms in `this`@entry
     */
    std::size_t nterms() const
    {
      return terms.size();
    }

    /*
     * Get the ith monomial term. No specific term ordering is guaranteed.
     */
    const monomial& term(std::size_t i) const
    {
      return terms[i];
    }


    /*
     * Evaluate this polynomial at the given args.
     *
     */
    template<typename ...X>
    scalar_type operator()(X&&... x) const
    {
      using S = std::common_type_t<scalar_type, X&&...>;
      // return evaluate_naive(*this, S(x)...);
      return evaluate_gH(*this, S(x)...);
    }

    /*
     * Get the coefficient of `i`th term in an additive represenation of `this` polynomial.
     * No specific term ordering is guaranteed.
     */
    scalar_type coefficient(std::size_t i) const
    {
      if(nterms() == 0)
        return scalar_type{0};
      else
        return terms[i].coefficient;
    }

    /*
     * Get the coefficient of the term with the given exponents.
     */
    scalar_type coefficient(const po::exponents& exponents) const
    {
      using namespace std::ranges;
      if(const auto found = find_if(
        terms,
        std::bind(equal, std::placeholders::_1, exponents),
        &monomial::exponents);
        found != std::cend(terms))
      {
        return found->coefficient;
      }
      else
      {
        return scalar_type{0};
      }
    }

    /*
     * Get the coefficient of the term with multiindex given by pack MI.
     */
    template<typename ...MI>
    constexpr scalar_type coefficient(MI... mi) const
    {
      return find_coefficient(terms, mi...);
    }

    /*
     * Get the coefficient of the term with multiindex given by pack MI.
     * If no such multiindex is found, a new term is added with that multiindex,
     * and a reference to its coefficient field is returned.
     */
    template<typename ...MI>
    constexpr scalar_type& coefficient(MI... mi)
    {
      return find_coefficient(terms, mi...);
    }

    /*
     * Add a monomial term with the given coefficient and exponents
     *
     * p.add(5.05, 3, 6);
     */
    template<typename ... MI>
      requires (std::integral<MI> && ...)
    constexpr void add(scalar_type c, MI&&... mi)
    {
      // TODO
      // if constexpr(((mi == exponent_type(0)) && ...))
      if (((mi == exponent_type(0)) && ...))
        constant_term += c;
      else
      {
        add_eq(terms, c, mi...);
        int i = 0;
        ((variable_degrees[i] = std::max(variable_degrees[i], exponent_type(mi)), ++i),...);
      }
    }

    /*
     * p.add_constant(8);
     * p.add_constant({8});
     */
    void add_constant(scalar_type c)
    {
      constant_term += c;
      add_eq_constant(terms, c, rank());
    }

    /*
     * Add a monomial term with the given coefficient and exponents
     *
     * p.add(5.05, {3, 6});
     */
    constexpr void add(scalar_type c, po::exponents&& exponents)
    {
      if(std::ranges::all_of(exponents, [](const exponent_type& x){ return x == 0; }))
        constant_term += c;
      else
        for(auto i{0zu}; i < rank(); ++i)
          variable_degrees[i] = std::max(variable_degrees[i], exponents[i]);

      add_eq(terms, c, std::forward<po::exponents>(exponents));
    }

    /*
     * Add a monomial term with the given coefficient and exponents
     *
     * p.add(5.05, exponents);
     */
    constexpr void add(scalar_type c, const po::exponents& exponents)
    {
      if(std::ranges::all_of(exponents, [](const exponent_type& x){ return x == 0; }))
        constant_term += c;
      else
        for(auto i{0zu}; i < rank(); ++i)
          variable_degrees[i] = std::max(variable_degrees[i], exponents[i]);

      add_eq(terms, c, exponents);
    }

    /*
     * Add an init-list of monomials.
     */
    constexpr void add(std::initializer_list<monomial>&& monomials)
    {
      for(auto& t : monomials)
        add(t.coefficient, t.exponents);
    }

    /*
     * Add a scalar constant.
     *
     * p += 6;
     */
    polynomial& operator+=(const scalar_type& c)
    {
      add_constant(c);
      return *this;
    }

    /*
     * Add a scalar constant.
     *
     * p += 6;
     * p += {6};
     */
    polynomial& operator+=(scalar_type&& c)
    {
      add_constant(c);
      return *this;
    }

    /*
     * Add a monomial term.
     */
    constexpr polynomial& operator+=(const monomial& t)
    {
      add(t.coefficient, t.exponents);
      return *this;
    }

    /*
     * Add a monomial term.
     *
     * p += {5.05, {3, 6}};
     */
    constexpr polynomial& operator+=(monomial&& t)
    {
      add(t.coefficient, std::forward<exponents>(t.exponents));
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
      add(std::move(t));
      return *this;
    }

    /*
     * Add a polynomial.
     *
     * p += std::move(q);
     */
    // TODO test
    polynomial& operator+=(polynomial&& q)
    {
      add_eq(terms, q.terms);

      for(const auto& t : terms)
      {
        if(t.degree() == 0)
          constant_term += t.coefficient;

        total_degree = std::max(total_degree, t.degree());

        for(auto i{0zu}; i < t.rank(); ++i)
          variable_degrees[i] = std::max(variable_degrees[i], t.exponents[i]);
      }

      return *this;
    }

    /*
     * Add a polynomial.
     *
     * p += q;
     */
    polynomial& operator+=(const polynomial& q)
    {
      add_eq(terms, q.terms);

      for(const auto& t : terms)
      {
        if(t.degree() == 0)
          constant_term += t.coefficient;

        total_degree = std::max(total_degree, t.degree());

        for(auto i{0zu}; i < t.rank(); ++i)
          variable_degrees[i] = std::max(variable_degrees[i], t.exponents[i]);
      }

      return *this;
    }

    /*
     * Replace this polynomial with its additive inverse.
     */
    polynomial& negate()
    {
      for(auto& t : terms)
        t.coefficient = -t.coefficient;
      return *this;
    }

    /*
     * Subtract an init-list of monomial terms.
     *
     * p.sub({9, {12, 1}}, {4.1, {0, 3}});
     */
    constexpr void sub(std::initializer_list<monomial>&& monomials)
    {
      for(auto& t : monomials)
        add(-t.coefficient, std::move(t.exponents));
    }

    /*
     * Subtract a polynomial.
     *
     * p -= std::move(q);
     */
    // TODO test
    polynomial& operator-=(polynomial&& q)
    {
      add_eq(terms, q.terms);

      for(const auto& t : terms)
      {
        if(t.degree() == 0)
          constant_term += t.coefficient;

        total_degree = std::max(total_degree, t.degree());

        for(auto i{0zu}; i < t.rank(); ++i)
          variable_degrees[i] = std::max(variable_degrees[i], t.exponents[i]);
      }

      return *this;
    }

    /*
     * Subtract a polynomial.
     *
     * p -= q;
     */
    polynomial& operator-=(const polynomial& q)
    {
      sub_eq(terms, q.terms);

      for(const auto& t : terms)
      {
        if(t.degree() == 0)
          constant_term += t.coefficient;

        total_degree = std::max(total_degree, t.degree());

        for(auto i{0zu}; i < t.rank(); ++i)
          variable_degrees[i] = std::max(variable_degrees[i], t.exponents[i]);
      }

      return *this;
    }

    /*
     * Subtract a scalar constant.
     *
     * p -= 6;
     * p -= {6};
     */
    polynomial& operator-=(scalar_type&& c)
    {
      add_constant(-c);
      return *this;
    }


    /*
     * Subtract a scalar constant.
     *
     * p -= 6;
     */
    polynomial& operator-=(scalar_type c)
    {
      add_constant(-c);
      return *this;
    }

    /*
     * Subtract a monomial term.
     *
     * p -= m;
     */
    constexpr polynomial& operator-=(const monomial& t)
    {
      add(-t.coefficient, t.exponents);
      return *this;
    }

    /*
     * Subtract a monomial term.
     *
     * p -= {5.05, {3, 6}};
     */
    constexpr polynomial& operator-=(monomial&& t)
    {
      add(-t.coefficient, std::forward<exponents>(t.exponents));
      return *this;
    }

    /*
     * Subtract an init-list of monomial terms.
     *
     * p -= {5, {3, 4, 2, 0, 4, 5}};
     * p -= {{5, {3, 4, 2, 0, 4, 5}}, {2.4, {0, 0, 2, 3, 4, 5}}};
     */
    constexpr polynomial& operator-=(std::initializer_list<monomial>&& t)
    {
      sub(std::move(t));
      return *this;
    }

    /*
     * p.multiply({1, {2, 3, 1}, {4.3, {0, 0, 4}}});
     */
    // TODO test
    void multiply(std::initializer_list<monomial>&& q)
    {
      mult_eq(terms, q);

      constant_term = scalar_type(0);
      total_degree = 0;

      for(const auto& t : terms)
      {
        if(t.degree() == 0)
          constant_term += t.coefficient;

        total_degree = std::max(total_degree, t.degree());

        for(auto i{0zu}; i < t.rank(); ++i)
          variable_degrees[i] = std::max(variable_degrees[i], t.exponents[i]);
      }
    }

    /*
     * p.multiply({1, {2, 3, 1}, {4.3, {0, 0, 4}}});
     */
    void multiply(po::polynomial&& q)
    {
      mult_eq(terms, q.terms);

      if(terms.size() == 0)
      {
        zero();
      }
      else
      {
        constant_term = scalar_type(0);
        total_degree = 0;

        for(const auto& t : terms)
        {
          if(t.degree() == 0)
            constant_term += t.coefficient;

          total_degree = std::max(total_degree, t.degree());

          for(auto i{0zu}; i < t.rank(); ++i)
            variable_degrees[i] = std::max(variable_degrees[i], t.exponents[i]);
        }
      }
    }

    /*
     * p.multiply(q);
     */
    void multiply(const po::polynomial& q)
    {
      mult_eq(terms, q.terms);

      if(terms.size() == 0)
      {
        zero();
      }
      else
      {
        constant_term = scalar_type(0);
        total_degree = 0;

        for(const auto& t : terms)
        {
          if(t.degree() == 0)
            constant_term += t.coefficient;

          total_degree = std::max(total_degree, t.degree());

          for(auto i{0zu}; i < t.rank(); ++i)
            variable_degrees[i] = std::max(variable_degrees[i], t.exponents[i]);
        }
      }
    }

    /*
     * p.multiply(5., {3, 2, 1, 2});
     */
    void multiply(scalar_type c, po::exponents&& exponents)
    {
      mult_eq(terms, c, exponents);

      if(terms.size() == 0)
      {
        zero();
      }
      else
      {
        variable_degrees += exponents;
        if(std::ranges::all_of(exponents, [](const exponent_type& x){ return x == 0; }))
          constant_term += c;
        else
          constant_term = scalar_type(0);
      }
    }

    /*
     * p.multiply(5., exponents);
     */
    void multiply(scalar_type c, const po::exponents& exponents)
    {
      mult_eq(terms, c, exponents);

      if(terms.size() == 0)
      {
        zero();
      }
      else
      {
        variable_degrees += exponents;
        if(std::ranges::all_of(exponents, [](const exponent_type& x){ return x == 0; }))
          constant_term += c;
        else
          constant_term = scalar_type(0);
      }
    }

    /*
     * Set this polynomial to be the zero polynomial.
     * This does not change this object's rank.
     */
    void zero()
    {
      terms.clear();
      constant_term = 0;
      total_degree = 0;
      variable_degrees = 0;
    }

    /*
     * Multiply by a scalar constant.
     *
     * p *= 6;
     * p *= {6};
     */
    polynomial& operator*=(scalar_type&& c)
    {
      mult_eq_scalar(terms, c);
      constant_term *= c;
      return *this;
    }

    /*
     * Multiply by a scalar constant.
     *
     * p *= scalar;
     * p *= scalar;
     */
    polynomial& operator*=(const scalar_type& c)
    {
      mult_eq_scalar(terms, c);
      constant_term *= c;
      return *this;
    }

    /*
     * Multiply by a monomial.
     *
     * p *= {5., {3, 2, 1, 2}};
     */
    polynomial& operator*=(monomial&& m)
    {
      multiply(m.coefficient, std::move(m.exponents));
      return *this;
    }

    /*
     * Multiply by a monomial.
     *
     * p *= monomial;
     */
    polynomial& operator*=(const monomial& t)
    {
      multiply(t.coefficient, t.exponents);
      return *this;
    }

    /*
     * Multiply by another polynomial.
     *
     * p *= q;
     */
    polynomial& operator*=(const polynomial& q)
    {
      multiply(q);
      return *this;
    }

    /*
     * Multiply by another polynomial.
     *
     * p *= std::move(q);
     */
    // TODO This function does not move q into p, for any q.
    // However, could make the case that p*=std::move(q) should move q into p iff
    // q is a factor of p@entry.
    // This could subsume fields from q. In that case, after this function
    // is called, the contents of q are undefined.
    polynomial& operator*=(polynomial&& q)
    {
      multiply(std::move(q));
      return *this;
    }

    /*
     * Multiply by an additive init-list of terms, without creating/moving a polynomial.
     *
     * p *= {{3, {2, 1, 4, 2}}, {6, {2, 2, 3, 2}}};
     */
    // TODO This function does not move the implied polynomial q into p, for any q.
    // However, could make the case that p*=std::move(q) should move q into p iff
    // q is a factor of p@entry.
    // This could subsume fields from q. In that case, after this function
    // is called, the contents of q are undefined.
    polynomial& operator*=(std::initializer_list<monomial>&& q)
    {
      multiply(std::move(q));
      return *this;
    }
  };

}

#endif

#include "ops/expr_partial_derivative.h"

#include "ops/instantiate.h"
