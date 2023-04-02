#ifndef PO_TRIE_FIND_COEFFICIENT_H
#define PO_TRIE_FIND_COEFFICIENT_H

#include "trie_vertex.h"
#include "trie_longest_prefix.h"
#include "../../types/scalar.h"
#include <vector>

namespace po
{
  /*
   * Get the offset into `coefficients` for the given path. If no such path exists,
   * `ABSENT` is returned.
   */
  std::size_t trie_find_coefficient(
    const std::vector<trie_vertex>& vertices,
    const std::vector<std::size_t>& roots,
    const po::exponents& exponents)
  {
    using namespace trie_constants;

    if(const auto [found_last, found_length] = trie_longest_prefix(vertices, roots, exponents); found_length < exponents.size())
    {
      return ABSENT;
    }
    else
    {
      // Get the pointer (or offset) to the child leaf.
      // A vertex which points to a leaf vertex has only one child.
      const std::size_t child_offset = vertices[found_last].children[0];

      // The value field of the child vertex is the pointer to (offset of) the coefficient.
      const std::size_t coefficient_offset = vertices[child_offset].value;

      return coefficient_offset;
    }
  }

  scalar_type trie_coefficient(
    const std::vector<trie_vertex>& vertices,
    const std::vector<std::size_t>& roots,
    const std::vector<scalar_type>& coefficients,
    const po::exponents& exponents)
  {
    using namespace trie_constants;

    if(const auto found{trie_find_coefficient(vertices, roots, exponents)}; found == ABSENT)
      return scalar_type(0);
    else
    {
      if(coefficients[found] != coefficients[found])
        return scalar_type{0};
      else
        return coefficients[found];
    }
  }
}

#endif


