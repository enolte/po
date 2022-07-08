#ifndef PO_INSTANTIATE_UNARY_PLUS_H
#define PO_INSTANTIATE_UNARY_PLUS_H

#include "expr_unary_plus.h"

#include "../ostream/polynomial_ostream.h"
#include "../test/macros.h"

namespace po
{
  template<typename E1, typename Rank>
  polynomial& instantiate(polynomial& p, expr_unary_plus<E1> expr, Rank&&)
  {
    // PO_LINE;
    instantiate(p, expr.expr1, Rank{});
    return p;
  }
}


#endif