#ifndef PO_ADD_EQ_CONSTANT_H
#define PO_ADD_EQ_CONSTANT_H

#include "../monomial.h"
#include "../field.h"
#include "find.h"

#include <vector>

namespace po
{
  void add_eq_constant(std::vector<monomial>& terms, scalar_type constant, std::size_t rank)
  {
    if(const auto found = find_constant(terms); found != std::cend(terms))
      found->coefficient += constant;
    else
      terms.emplace_back(constant, po::exponents(exponent_type{0}, rank));
  }
}


#endif

