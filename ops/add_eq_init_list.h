#ifndef PO_ADD_EQ_INIT_LIST_H
#define PO_ADD_EQ_INIT_LIST_H

#include "add_eq_monomial.h"

namespace po
{
  /*
   * Add a polynomial.
   *
   */
  constexpr void add_eq(std::vector<monomial>& terms, const std::initializer_list<monomial>& q)
  {
    for(const auto& t : q)
      add_eq(terms, t.coefficient, t.exponents);
  }
}

#endif


