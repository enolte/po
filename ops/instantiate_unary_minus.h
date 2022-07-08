#ifndef PO_INSTANTIATE_UNARY_MINUS_H
#define PO_INSTANTIATE_UNARY_MINUS_H

#include "expr_unary_minus.h"

#include "../ostream/polynomial_ostream.h"
#include "../test/macros.h"

namespace po
{
  template<typename E1, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_unary_minus<E1> expr, Rank&&)
  {
    // PO_LINE;
    instantiate(p, expr.expr1, Rank{});
    p.negate();
    return p;
  }

}


#endif