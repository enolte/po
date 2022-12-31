#ifndef PO_TRIE_VERTEX_H
#define PO_TRIE_VERTEX_H

#include <vector>

#include "trie_constants.h"

namespace po
{
  struct trie_vertex
  {
    /*
     * For an internal vertex, this is the exponent value for that vertex.
     * For a leaf vertex, this is the offset into `coefficients` of the coefficient
     * value for the multiindex path.
     */
    std::size_t value = trie_constants::ABSENT;

    /*
     * The value of child[i] is the offset into `vertices` for the ith child
     * vertex of this vertex. For a leaf vertex, this vector is empty.
     */
    std::vector<std::size_t> children;

    /*
     * The level of this vertex in the trie. level == 0 iff this vertex is a root.
     */
    std::size_t level = trie_constants::ABSENT;

    // (These friends decls are necessary for defaulted comparison impls. Ugh.)
    friend bool operator==(const po::trie_vertex& a, const po::trie_vertex& b);
    friend bool operator!=(const po::trie_vertex& a, const po::trie_vertex& b);
  };

  bool operator==(const po::trie_vertex& a, const po::trie_vertex& b) = default;
  bool operator!=(const po::trie_vertex& a, const po::trie_vertex& b) = default;

}

#endif

