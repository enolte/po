#ifndef PO_TRIE_H
#define PO_TRIE_H

#include <cassert>

#include "exponents.h"
#include "field.h"

#include "trie/trie_vertex.h"
#include "trie/trie_constants.h"

#include "trie/trie_add.h"
#include "trie/trie_remove.h"
#include "trie/trie_find_coefficient.h"

namespace po
{
  struct trie
  {
    using vertex = trie_vertex;

    /*
     * A container for `vertex` instances.
     */
    std::vector<vertex> vertices;

    /*
     * An offset into `vertices` for each root vertex.
     */
    std::vector<std::size_t> roots;

    /*
     * Leaf coefficients
     */
    std::vector<scalar_type> coefficients;

    /*
     * Get the coefficient of the given exponents multiindex. If there is no such stored
     * multiindex, the coefficient is zero.
     */
    scalar_type coefficient(const po::exponents& exponents) const
    {
      using namespace trie_constants;

      if(const auto found{trie_find_coefficient(vertices, roots, coefficients, exponents)}; found == ABSENT)
        return scalar_type(0);
      else
        return coefficients[found];
    }

    /*
     * Add the fields of a monomial term to the tree.
     */
    void add(scalar_type&& c, po::exponents&& exponents)
    {
      trie_add(vertices, roots, coefficients, std::move(c), std::move(exponents));
    }


    /*
     * Virtual removal: Set the leaf coefficient to nan. Leave the path in place.
     */
    void remove(const po::exponents& exponents)
    {
      trie_remove(vertices, roots, coefficients, exponents);
    }


  };

}

#endif

