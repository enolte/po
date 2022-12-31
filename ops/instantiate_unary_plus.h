#ifndef PO_INSTANTIATE_UNARY_PLUS_H
#define PO_INSTANTIATE_UNARY_PLUS_H

#include "expr_unary_plus.h"

namespace po
{
  template<typename E1>
  polynomial& instantiate(polynomial& p, const expr_unary_plus<E1> expr, rank_type rank)
  {
    instantiate(p, expr.expr1, rank);
    return p;
  }
}

#endif
