#ifndef PO_INSTANTIATE_UNARY_MINUS_H
#define PO_INSTANTIATE_UNARY_MINUS_H

#include "expr_unary_minus.h"

namespace po
{
  template<typename E1>
  polynomial& instantiate(polynomial& p, const expr_unary_minus<E1> expr, rank_type rank)
  {
    instantiate(p, expr.expr1, rank);
    p *= -1;
    return p;
  }
}

#endif