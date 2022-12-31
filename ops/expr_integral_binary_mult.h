#ifndef PO_EXPR_INTEGRAL_BINARY_MULT_H
#define PO_EXPR_INTEGRAL_BINARY_MULT_H

#include "expr_rank.h"

namespace po
{
  template<typename E1, typename E2>
  struct expr_integral<expr_binary_mult<E1, E2>>
  {
    using _E1 = expr_binary_mult<E1, E2>;
    using F1 = expr_field_type<expr_binary_mult<E1, E2>>;

    const F1 expr1;
    const rank_type place;
    const scalar_type a, b;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      // TODO Without instantiation, maybe
      const rank_type rank = expr_rank(expr1);
      return instantiate(*this, rank)(x...);
    }
  };

}

#endif

