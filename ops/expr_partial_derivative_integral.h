#ifndef PO_EXPR_PARTIAL_DERIVATIVE_INTEGRAL_H
#define PO_EXPR_PARTIAL_DERIVATIVE_INTEGRAL_H

#include "expr_integral.h"

namespace po
{
  template<expression E1>
  struct expr_partial_derivative<expr_integral<E1>>
  {
    using _E1 = expr_integral<E1>;
    using F1 = subexpr_type<expr_integral<E1>>;

    const F1 expr1;

    const rank_type place;

    template<scalar ...X>
    scalar_type operator()(X... x) const
    {
      // TODO without instantitation
      auto p = instantiate(expr1);
      return D(p, place)(x...);
    }
  };

  template<expression E1>
  struct expr_partial_derivative<const expr_integral<E1>&>
  {
    using _E1 = expr_integral<E1>;
    using F1 = subexpr_type<const expr_integral<E1>&>;

    const F1 expr1;

    const rank_type place;

    template<scalar ...X>
    scalar_type operator()(X... x) const
    {
      auto p = instantiate(expr1);
      return D(p, place)(x...);
    }
  };

}

#endif



