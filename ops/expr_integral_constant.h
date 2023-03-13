#ifndef PO_EXPR_INTEGRAL_CONSTANT_H
#define PO_EXPR_INTEGRAL_CONSTANT_H

#include "expr_constant.h"

namespace po
{
  template<>
  struct expr_integral<expr_constant>
  {
    using _E1 = expr_constant;
    using F1 = subexpr_type<expr_constant>;

    const F1 expr1;
    const rank_type place;
    const scalar_type a, b;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return expr1.expr1 * (b - a);
    }
  };

  template<>
  struct expr_integral<scalar_type>
  {
    using _E1 = scalar_type;
    using F1 = subexpr_type<scalar_type>;

    const F1 expr1;
    const rank_type place;
    const scalar_type a, b;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return expr1 * (b - a);
    }
  };


}

#endif

