#ifndef PO_INSTANTIATE_BINARY_MINUS_H
#define PO_INSTANTIATE_BINARY_MINUS_H

#include "expr_binary_minus.h"


namespace po
{
  template<typename E1, typename E2>
  polynomial& instantiate(polynomial& p, const expr_binary_minus<E1, E2> expr, rank_type rank)
  {
    if constexpr (is_nullary_expression<E2>)
    {
      return (instantiate(p, expr.expr1, rank) -= expr.expr2);
    }
    else
    {
      polynomial right{};
      return (instantiate(p, expr.expr1, rank) -= instantiate(right, expr.expr2, rank));
    }
  }
}


#endif

