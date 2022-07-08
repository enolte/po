#ifndef PO_ADD_EQ_POLYNOMIAL_H
#define PO_ADD_EQ_POLYNOMIAL_H

#include "add_eq_monomial.h"

namespace po
{
  /*
   * Add a polynomial.
   *
   */
  void add_eq(std::vector<monomial>& terms, const std::vector<monomial>& q)
  {
    for(const auto& t : q)
      add_eq(terms, t.coefficient, t.exponents);
  }
}

#endif


