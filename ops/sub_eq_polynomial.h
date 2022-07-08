#ifndef PO_SUB_EQ_POLYNOMIAL_H
#define PO_SUB_EQ_POLYNOMIAL_H

#include "sub_eq_monomial.h"

namespace po
{
  /*
   * Subtract a polynomial.
   *
   */
  void sub_eq(std::vector<monomial>& terms, const std::vector<monomial>& q)
  {
    for(const auto& t : q)
      sub_eq(terms, t.coefficient, t.exponents);
  }
}

#endif
