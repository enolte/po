#ifndef PO_TRIE_REMOVE_H
#define PO_TRIE_REMOVE_H

#include "trie_vertex.h"
#include "trie_longest_prefix.h"
#include "../../field.h"
#include <vector>

namespace po
{
  /*
   * Virtual removal: If the leaf coefficient exists and is not nan,
   * set the leaf coefficient to nan, else do nothing.
   *
   * In either case, leave the path in place.
   *
   * return true iff the path was found and the data was set to nan.
   */
  bool trie_remove(
    const std::vector<trie_vertex>& vertices,
    const std::vector<std::size_t>& roots,
    std::vector<scalar_type>& coefficients,
    const po::exponents& exponents)
  {
    using namespace trie_constants;

    const auto [found_last, found_length] = trie_longest_prefix(vertices, roots, exponents);

    if(found_length < exponents.size())
      return false;

    // Get the offset to the child leaf.
    // A vertex which points to a leaf vertex has only one child.
    const std::size_t child_offset = vertices[found_last].children[0];

    // The value field of the child vertex is the offset of the coefficient.
    const std::size_t coefficient_offset = vertices[child_offset].value;

    scalar_type& c = coefficients[coefficient_offset];
    if(c == c)
    {
      c = absent_value;
      return true;
    }

    return false;
  }

}

#endif


