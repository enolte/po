#ifndef PO_INSTANTIATE_POLYNOMIAL_H
#define PO_INSTANTIATE_POLYNOMIAL_H

#include "../polynomial.h"

namespace po
{
  template<typename Rank>
  polynomial& instantiate(polynomial& p, const polynomial& expr, Rank&&)
  {
    p = expr;
    return p;
  }

}


#endif