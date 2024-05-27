#ifndef PO_INSTANTIATE_POLYNOMIAL_H
#define PO_INSTANTIATE_POLYNOMIAL_H

#include "../polynomial.h"

namespace po
{
  static polynomial& instantiate(polynomial& p, const polynomial& expr, rank_type)
  {
    p = expr;
    return p;
  }

}


#endif

