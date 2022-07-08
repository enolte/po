#ifndef PO_INSTANTIATE_CONSTANT_H
#define PO_INSTANTIATE_CONSTANT_H

#include "expr_constant.h"

#include "../ostream/polynomial_ostream.h"
#include "../test/macros.h"

namespace po
{
  template<typename Rank>
  polynomial& instantiate(polynomial& p, const expr_constant& expr, Rank&&)
  {
    // PO_LINE; PO_TRACE("terminal: scalar = " << expr.expr1);
    p = polynomial(expr.expr1, Rank{});
    return p;
  }


}


#endif