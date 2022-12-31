#ifndef PO_INSTANTIATE_BINARY_MINUS_H
#define PO_INSTANTIATE_BINARY_MINUS_H

#include "expr_binary_minus.h"

namespace po
{
  template<typename E1, typename E2>
  polynomial& instantiate(polynomial& p, const expr_binary_minus<E1, E2> expr, rank_type rank)
  {
    instantiate(p, expr.expr1, rank);
    polynomial right = polynomial::make_zero(rank);
    instantiate(right, expr.expr2, rank);

    p -= right;

    return p;
  }
}


#endif