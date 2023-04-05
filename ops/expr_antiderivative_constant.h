#ifndef PO_EXPR_ANTIDERIVATIVE_CONSTANT_H
#define PO_EXPR_ANTIDERIVATIVE_CONSTANT_H

#include "expr_constant.h"

namespace po
{
  template<>
  struct expr_antiderivative<expr_constant>
  {
    using _E1 = expr_constant;
    using F1 = subexpr_type<expr_constant>;

    const F1 expr1;
    const rank_type place;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      int i = -1;
      double acc = 1.;
      (
        (acc *= (x != x ? nan : ++i == place ? x : 1.)), ...
      );

      return expr1.expr1 * acc;
    }
  };

  template<>
  struct expr_antiderivative<scalar_type>
  {
    using _E1 = scalar_type;
    using F1 = subexpr_type<scalar_type>;

    const F1 expr1;
    const rank_type place;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      int i = -1;
      double acc = 1.;
      (
        (acc *= (x != x ? nan : ++i == place ? x : 1.)), ...
      );

      return expr1 * acc;
    }
  };


}

#endif

