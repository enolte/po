#ifndef PO_EXPR_ANTIDERIVATIVE_BINARY_MULT_H
#define PO_EXPR_ANTIDERIVATIVE_BINARY_MULT_H

#include "expr_rank.h"

namespace po
{
  template<typename E1, typename E2>
  struct expr_antiderivative<expr_binary_mult<E1, E2>>
  {
    using _E1 = expr_binary_mult<E1, E2>;
    using F1 = subexpr_type<expr_binary_mult<E1, E2>>;

    const F1 expr1;
    const rank_type place;


    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      // TODO Without instantiation, probably
      return instantiate(*this)(x...);
    }
  };

}

#endif

