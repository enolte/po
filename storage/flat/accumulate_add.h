#ifndef PO_STORAGE_FLAT_ACC_ADD_H
#define PO_STORAGE_FLAT_ACC_ADD_H

#include "find_term.h"

namespace po
{
  inline namespace flat_model
  {
    /*
     * Accumulate a scalar and exponents, implements addition.
     */
    static constexpr void accumulate_add(storage& terms, scalar_type c, const po::exponents& exponents)
    {
      if(auto found = find_term(terms, exponents); found != std::cend(terms))
        found->coefficient += c;
      else
        terms.emplace_back(c, exponents);
    }

    /*
     * Accumulate a scalar and exponents, implements addition.
     */
    static constexpr void accumulate_add(storage& terms, scalar_type c, po::exponents&& exponents)
    {
      if(auto found = find_term(terms, exponents); found != std::cend(terms))
        found->coefficient += c;
      else
        terms.emplace_back(c, std::move(exponents));
    }
  }
}

#endif

