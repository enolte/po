#ifndef PO_STORAGE_TRIE_ACC_ADD_H
#define PO_STORAGE_TRIE_ACC_ADD_H

#include "find_term.h"

namespace po
{
  inline namespace trie_model
  {
    /*
     * Accumulate a scalar and exponents, implements addition.
     */
    // TODO Test
    static void accumulate_add(storage& terms, scalar_type&& c, po::exponents&& exponents)
    {
      terms.insert(std::forward<scalar_type>(c), std::forward<po::exponents>(exponents));
    }

#if 0
    // TODO
    /*
     * Accumulate a scalar and exponents, implements addition.
     */
    constexpr static void accumulate_add(storage& terms, scalar_type c, po::exponents&& exponents)
    {
      terms.insert(std::forward<scalar_type>(c), std::forward<po::exponents>(exponents));
    }
#endif
  }
}

#endif

