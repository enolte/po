#ifndef PO_EXPR_PARTIAL_DERIVATIVE_POLYNOMIAL_H
#define PO_EXPR_PARTIAL_DERIVATIVE_POLYNOMIAL_H

#include "../utils.h"

namespace po
{
  namespace detail
  {
    template<is_polynomial P, typename ...X>
    scalar_type evaluate(const P& expr1, rank_type place, X... x);

    template<is_polynomial E1>
    struct expr_partial_derivative_polynomial
    {
      using _E1 = E1;
      using F1 = subexpr_type<E1>;

      const F1 expr1;
      const rank_type place;

      /*
       * Naive implementation. Evaluate a partial derivative of this polynomial. Compute the result as a `double`, then
       * return the static cast to `scalar_type`.
       */
      template<typename ...X>
      constexpr scalar_type operator()(X... x) const
      {
        return detail::evaluate(expr1, place, x...);
      }
    };
  }

  template<>
  struct expr_partial_derivative<polynomial&>
  : detail::expr_partial_derivative_polynomial<polynomial&>
  {};

  template<>
  struct expr_partial_derivative<const polynomial&>
  : detail::expr_partial_derivative_polynomial<const polynomial&>
  {};

  template<>
  struct expr_partial_derivative<polynomial>
  : detail::expr_partial_derivative_polynomial<polynomial>
  {};

  template<>
  struct expr_partial_derivative<const polynomial>
  : detail::expr_partial_derivative_polynomial<const polynomial>
  {};

  namespace detail
  {
    template<typename ...X>
    scalar_type evaluate(const monomial& m, rank_type place, X... x);

    template<is_polynomial P, typename ...X>
    scalar_type evaluate(const P& expr1, rank_type place, X... x)
    {
      if(sizeof ...(X) != expr1.rank())
        return 0./0.;

      if(place >= expr1.rank())
        return scalar_type{0};

      double acc = 0.;
      for(const auto& t : expr1.terms)
        acc += evaluate(t, place, x...);

      return scalar_type{acc};
    }

    template<typename ...X>
    scalar_type evaluate(const monomial& m, rank_type place, X... x)
    {
      if(sizeof ...(X) != m.rank())
        return 0./0.;

      if(place >= m.rank())
        return scalar_type{0};

      if(m.exponents[place] == 0)
        return scalar_type{0};

      double acc = 1.;
      std::size_t i = 0;
      (
        (i == place
          ? acc *= utils::pow(x, m.exponents[i++] - 1)
          : acc *= utils::pow(x, m.exponents[i++])),
        ...
      );

      return scalar_type{acc * m.coefficient * m.exponents[place]};
    }
  }

}

#endif


