#ifndef PO_TRIE_ADD_H
#define PO_TRIE_ADD_H

#include "trie_vertex.h"
#include "trie_longest_prefix.h"
#include "trie_get_path.h"
#include "../../field.h"
#include <vector>
#include <tuple>

namespace po
{
  /*
   * Emplace the given coefficient at the first-found memory address in the continguous
   * sequence of coefficients values. If no nan is found, the vector is resized and the new
   * coefficient is placed at the end.
   *
   * return: the offset at which the new coefficient is emplaced.
   *
   * N.B.: Every coefficient offset has a unique path which points to it, so it isn't strictly
   *       necessary to return the offset here, because this called only when a new path
   *       is being added, which means we already know where the new coefficient offset:
   *       it is {size of coefficients@entry}.
   *
   *       This function should not assume its own use cases, though, so just return the value.
   */
  std::size_t emplace_new_coefficient(std::vector<scalar_type>& coefficients, scalar_type&& c)
  {
    for(auto i{0zu}; i < coefficients.size(); ++i)
    {
      if(coefficients[i] != coefficients[i])
      {
        coefficients[i] = std::move(c);
        return i;
      }
    }

    coefficients.emplace_back(std::move(c));
    return coefficients.size() - 1;
  }

  /*
   * Add a term with the given `exponents` to the given `vertices` with the given `roots`.
   *
   * If the given path already exists, the coefficient `c` is added to the found coefficient.
   * If the given path DNE at entry, it is created.
   *
   * return: true iff a new path was created.
   */
  bool trie_insert(
    std::vector<trie_vertex>& vertices,
    std::vector<std::size_t>& roots,
    std::vector<scalar_type>& coefficients,
    scalar_type&& c,
    po::exponents&& exponents)
  {
    auto [last_vertex, is_new_path] = trie_get_path(vertices, roots, exponents);

    if(is_new_path)
    {
      // Add a new leaf:

      // Emplace a new scalar.
      // N.B.: We already know this new offset == {size of coefficients@entry}, but it does
      // no harm to copy it here.
      const std::size_t new_coefficient_offset = emplace_new_coefficient(coefficients, 0);

      // Create a new leaf vertex to point to the new scalar
      vertices.emplace_back(trie_vertex{new_coefficient_offset, {}});

      // Make the new leaf a child of the current last vertex
      vertices[last_vertex].children.push_back(vertices.size() - 1);
    }

    // Move to the leaf for the key path.
    last_vertex = vertices[last_vertex].children[0];

    scalar_type& cc = coefficients[vertices[last_vertex].value];
    if(cc != cc)
      cc = c;
    else
      cc += c;

    return is_new_path;
  }
}

#endif


