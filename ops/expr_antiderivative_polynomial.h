#ifndef PO_EXPR_ANTIDERIVATIVE_POLYNOMIAL_H
#define PO_EXPR_ANTIDERIVATIVE_POLYNOMIAL_H

#include "../utils/pow.h"
#include "../utils/nan.h"
#include "../ostream/monomial_ostream.h"
namespace po
{
  namespace detail
  {
    template<is_polynomial P, is_scalar ...X>
    constexpr scalar_type evaluate_antiderivative(const P& expr1, rank_type place, X&&... x);

    template<is_polynomial E1>
    struct expr_antiderivative
    {
      using _E1 = E1;
      using F1 = subexpr_type<E1>;

      const F1 expr1;
      const rank_type place;

      template<typename ...X>
      constexpr scalar_type operator()(X&&... x) const
      {
        return detail::evaluate_antiderivative(expr1, place, x...);
      }
    };
  }

  template<>
  struct expr_antiderivative<polynomial&>
  : detail::expr_antiderivative<polynomial&>
  {};

  template<>
  struct expr_antiderivative<const polynomial&>
  : detail::expr_antiderivative<const polynomial&>
  {};

  template<>
  struct expr_antiderivative<polynomial>
  : detail::expr_antiderivative<polynomial>
  {};

  template<>
  struct expr_antiderivative<const polynomial>
  : detail::expr_antiderivative<const polynomial>
  {};

  namespace detail
  {
    template<scalar ...X>
    constexpr scalar_type value(rank_type place, X&&... x);

    template<is_polynomial P, is_scalar ...X>
    constexpr scalar_type evaluate_antiderivative(const P& expr1, rank_type place, X&&... x)
    {
      if(place >= expr1.rank())
      {
        if(sizeof ...(X) != place + 1)
          return nan;

        return evaluate(nargs{expr1.rank()}, expr1, x...) * value(place, x...);
      }
      else
      {
        if(sizeof ...(X) != expr1.rank())
          return nan;

        const scalar_type v = value(place, x...);

        double acc = 0.;
        for(const auto& t : expr1.terms)
          acc += t(x...) * v / (t.exponents[place] + 1);

        return scalar_type{acc};
      }
    }

    // TODO This could be done better.
    template<scalar ...X>
    constexpr scalar_type value(rank_type place, X&&... x)
    {
      rank_type i = 0;
      scalar_type v = scalar_type{1};
      (
        (
          v *= (i == place)*x  +  (i != place),
          ++i
        ),
        ...
      );

      return v;
    }
  }

}

#endif

