#ifndef PO_INSTANTIATE_POLYNOMIAL_H
#define PO_INSTANTIATE_POLYNOMIAL_H

#include "../polynomial.h"

#include "../ostream/polynomial_ostream.h"
#include "../test/macros.h"

namespace po
{
  template<typename Rank>
  polynomial& instantiate(polynomial& p, const polynomial& expr, Rank&&)
  {
    // PO_LINE; PO_TRACE("terminal: polynomial = " << expr);
    p = expr;
    return p;
  }

}


#endif