#ifndef PO_STORAGE_TRIE_CONSTANT_H
#define PO_STORAGE_TRIE_CONSTANT_H

#include "find_term.h"

namespace po
{
  inline namespace trie_model
  {
    // TODO Test
    static scalar_type find_coefficient(const storage& terms, const po::exponents& exponents)
    {
      if(const auto found = find_term(terms, exponents); found != std::cend(terms.monomials()))
        return found->coefficient;
      else
        return scalar_type{0};
    }
  }
}

#endif


