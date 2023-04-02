#ifndef PO_TRIE_LONGEST_PREFIX_H
#define PO_TRIE_LONGEST_PREFIX_H

#include "trie_vertex.h"
#include "trie_constants.h"
#include "../../types/exponents.h"

namespace po
{
  /*
   * Given an exponent value, get the offset into `vertices` of the root
   * which has value exponent[0].
   *
   * If no such root exists, return ABSENT.
   */
  std::size_t trie_find_root(
    const std::vector<trie_vertex>& vertices,
    const std::vector<std::size_t>& roots,
    const po::exponents& exponents)
  {
    using namespace trie_constants;

    for(auto root_offset : roots)
      if(vertices[root_offset].value == exponents[0])
        return root_offset;

    return ABSENT;
  }

  /*
   * For the given `vertices`, get the offset into `vertices` of the unique child of the
   * `last` vertex which has value == `exponent`.
   *
   * If no such child exists, `ABSENT` is returned.
   */
  std::size_t trie_vertex_get_child(const std::vector<trie_vertex>& vertices, std::size_t last, exponent_type exponent)
  {
    using namespace trie_constants;

    const auto& children = vertices[last].children;

    for(auto child : children)
      if(vertices[child].value == exponent)
        return child;

    return ABSENT;
  }

  /*
   * Find the longest prefix of the path `exponents` in `vertices`.
   *
   * The return value is the tuple {last, length}, where
   *
   *  last = offset into `vertices` of the last found vertex in the path. This `value` field
   *  of this vertex is the last found exponent value in the given `exponents`.
   *
   *  length = length of the prefix of `exponents` discovered. This is the offset into `exponents`
   *  of the last found exponent value.
   *
   * The entire path is found iff length == `exponents.size()`.
   *
   * If the entire path is absent, {ABSENT, 0} is returned.
   */
  std::tuple<std::size_t, std::size_t> trie_longest_prefix(
    const std::vector<trie_vertex>& vertices,
    const std::vector<std::size_t>& roots,
    const po::exponents& exponents)
  {
    using namespace trie_constants;

    if(vertices.size() == 0)
      return {ABSENT, 0};

    // Find the root
    std::size_t root_offset = trie_find_root(vertices, roots, exponents);
    if(root_offset == ABSENT)
      return {ABSENT, 0};

    // Exhaust the length
    std::size_t last = root_offset;
    std::size_t length = 1;
    while(length < exponents.size())
    {
      const std::size_t next = trie_vertex_get_child(vertices, last, exponents[length]);
      if(next == ABSENT)
        break;

      last = next;

      ++length;
    }

    return {last, length};
  }
}

#endif


