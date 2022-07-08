#ifndef PO_MULT_EQ_MONOMIAL_H
#define PO_MULT_EQ_MONOMIAL_H

#include "find.h"

#include "../field.h"
#include "../monomial.h"

namespace po
{
  /*
   * Multiply a polynomial by a monomial
   *
   */
  void mult_eq(std::vector<monomial>& terms, const scalar_type& c, const po::exponents& exponents)
  {
    for(auto& term : terms)
    {
      term.exponents += exponents;
      term.coefficient *= c;
    }
  }
}

#endif


