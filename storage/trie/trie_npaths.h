#ifndef PO_TRIE_NPATHS_H
#define PO_TRIE_NPATHS_H

#include <vector>

namespace po
{
  /*
   * Get the number of paths in the tree. This includes any (virtually) deleted terms.
   */
  std::size_t trie_npaths(const std::vector<scalar_type>& coefficients)
  {
    return coefficients.size();
  }
}

#endif


