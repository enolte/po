#ifndef PO_INSTANTIATE_BINARY_MULT_H
#define PO_INSTANTIATE_BINARY_MULT_H

#include "expr_binary_mult.h"

#include "../ostream/polynomial_ostream.h"
#include "../test/macros.h"

namespace po
{
  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_binary_mult<E1, E2> expr, Rank&&)
  {
    // PO_LINE;
    instantiate(p, expr.expr1, Rank{});
    polynomial right{Rank{}};
    instantiate(right, expr.expr2, Rank{});

    p *= right;

    return p;
  }
}


#endif