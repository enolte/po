#ifndef PO_TRIE_NTERMS_H
#define PO_TRIE_NTERMS_H

#include <vector>
#include <algorithm>

namespace po
{
  /*
   * Get the number of terms in the polynomial represented here. This is equal
   * the number of logical paths in this instance.
   */
  std::size_t trie_nterms(const std::vector<scalar_type>& coefficients)
  {
    return std::ranges::count_if(coefficients, [](scalar_type c) { return c == c; });
  }
}

#endif