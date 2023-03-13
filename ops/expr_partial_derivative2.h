#ifndef PO_EXPR_PARTIAL_DERIVATIVE2_H
#define PO_EXPR_PARTIAL_DERIVATIVE2_H

#include "expr_rank.h"

namespace po
{
  template<expression E1>
  struct expr_partial_derivative<expr_partial_derivative<E1>>
  {
    using _E1 = expr_partial_derivative<E1>;
    using F1 = subexpr_type<expr_partial_derivative<E1>>;

    const F1 expr1;
    const rank_type place;

    template<typename ...X>
    constexpr scalar_type operator()(X... x) const;
  };
}

namespace po
{
  template<expression E1>
  template<typename ...X>
  constexpr scalar_type expr_partial_derivative<expr_partial_derivative<E1>>::operator()(X... x) const
  {
    // TODO Evaluate without intantiating.
    const rank_type rank = expr_rank(expr1);
    return instantiate(*this, rank)(x...);
  }
}

#endif


