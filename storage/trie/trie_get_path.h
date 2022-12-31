#ifndef PO_TRIE_GET_PATH_H
#define PO_TRIE_GET_PATH_H

#include "trie_vertex.h"
#include "trie_longest_prefix.h"

#include <tuple>

namespace po
{
  /*
   * Find the path of `exponents` if it exists, else create it.
   *
   * N.B.: This does not create the leaf vertex after the last exponent vertex.
   *
   * return: a tuple(last_vertex, is_new_path), where
   *  last_vertex is the offset into `vertices` of the last vertex in the exponent path.
   *  is_new_path == true iff a new path was constructed by this function call.
   *
   *  The value of last_vertex identifies the vertex that contains the last exponent.
   */
  std::tuple<std::size_t, bool> trie_get_path(
    std::vector<trie_vertex>& vertices,
    std::vector<std::size_t>& roots,
    const po::exponents& exponents)
  {
    auto [last_vertex, length] = trie_longest_prefix(vertices, roots, exponents);

    const bool is_new_path = length < exponents.size();

    if(length == 0)
    {
      vertices.emplace_back(trie_vertex{exponents[0], {}, length});
      roots.push_back(vertices.size() - 1);
      last_vertex = vertices.size() - 1;
      ++length;
    }

    while(length < exponents.size())
    {
      // Create a new vertex with the next exponent value
      vertices.emplace_back(trie_vertex{exponents[length], {}, length});

      // Make the new vertex a child of the current last vertex
      vertices[last_vertex].children.push_back(vertices.size() - 1);

      // Move to the new last vertex
      last_vertex = vertices.size() - 1;

      ++length;
    }

    return {last_vertex, is_new_path};
  }
}

#endif


