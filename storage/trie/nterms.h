#ifndef PO_STORAGE_TRIE_NTERMS_H
#define PO_STORAGE_TRIE_NTERMS_H

#include "trie_nterms.h"

#include <algorithm>

namespace po
{
  inline namespace trie_model
  {
    /*
     * Get the number of terms in the polynomial represented here. This is equal
     * the number of logical paths in the trie storage instance.
     */
    constexpr std::size_t nterms(const storage& terms)
    {
      return std::ranges::count_if(terms.coefficients, [](scalar_type c) { return c == c; });
    }
  }
}

#endif