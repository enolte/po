#ifndef PO_MULT_EQ_SCALAR_H
#define PO_MULT_EQ_SCALAR_H

#include "find.h"

#include "../field.h"
#include "../monomial.h"

namespace po
{
  /*
   * Multiply a polynomial by a scalar
   *
   */
  void mult_eq_scalar(std::vector<monomial>& terms, scalar_type s)
  {
    for(auto& term : terms)
      term.coefficient *= s;
  }


}

#endif


