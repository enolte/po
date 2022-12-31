#ifndef PO_EXPR_INTEGRAL_POLYNOMIAL_H
#define PO_EXPR_INTEGRAL_POLYNOMIAL_H

#include "../utils.h"

namespace po
{
  namespace detail
  {
    template<is_polynomial P, typename ...X>
    scalar_type evaluate(const P& expr1, rank_type place, scalar_type a, scalar_type b, X... x);

    template<is_polynomial E1>
    struct expr_integral
    {
      using _E1 = E1;
      using F1 = expr_field_type<E1>;

      const F1 expr1;
      const rank_type place;
      const scalar_type a, b;

      template<typename ...X>
      constexpr scalar_type operator()(X... x) const
      {
        return detail::evaluate(expr1, place, a, b, x...);
      }
    };
  }

  template<>
  struct expr_integral<polynomial&>
  : detail::expr_integral<polynomial&>
  {};

  template<>
  struct expr_integral<const polynomial&>
  : detail::expr_integral<const polynomial&>
  {};

  template<>
  struct expr_integral<polynomial>
  : detail::expr_integral<polynomial>
  {};

  template<>
  struct expr_integral<const polynomial>
  : detail::expr_integral<const polynomial>
  {};

  namespace detail
  {
    template<typename ...X>
    scalar_type evaluate(const monomial& m, rank_type place, scalar_type a, scalar_type b, X... x);

    template<is_polynomial P, typename ...X>
    scalar_type evaluate(const P& expr1, rank_type place, scalar_type a, scalar_type b, X... x)
    {
        if(sizeof ...(X) != expr1.rank() - 1)
          return 0./0.;

        if(place >= expr1.rank())
          return expr1(x...) * (b - a);

        double acc = 0.;
        for(const auto& t : expr1.terms)
          acc += evaluate(t, place, a, b, x...);

        return scalar_type{acc};
    }

    template<typename ...X>
    scalar_type evaluate(const monomial& m, rank_type place, scalar_type a, scalar_type b, X... x)
    {
      if(m.exponents[place] == 0)
        return m(x...) * (b - a);

      double acc = 1.;
      std::size_t i = 0;
      (
        (
          acc *= utils::pow(x, m.exponents[ i + (i >= place) ]),
          ++i
        ),
        ...
      );

      acc *= utils::pow(b, m.exponents[place] + 1) - utils::pow(a, m.exponents[place] + 1);
      acc /= (m.exponents[place] + 1);

      return scalar_type{acc * m.coefficient};
    }
  }

}

#endif

