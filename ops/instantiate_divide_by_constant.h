#ifndef PO_INSTANTIATE_DIVIDE_BY_CONSTANT_H
#define PO_INSTANTIATE_DIVIDE_BY_CONSTANT_H

#include "expr_binary_divide_by_constant.h"
#include "instantiate_binary_mult.h"

namespace po
{
  polynomial& instantiate(polynomial& p, const expr_binary_divide_by_constant<expression auto, constant auto> expr, rank_type rank)
  {
    return instantiate(p, expr.expr1, rank) /= expr.expr2;
  }
}


#endif

