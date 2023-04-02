#ifndef PO_TRIE_H
#define PO_TRIE_H

#include <vector>

#include "../../types/exponents.h"
#include "../../types/monomial.h"
#include "../../types/scalar.h"

#include "trie_vertex.h"

#include "trie_npaths.h"
#include "trie_nterms.h"
#include "trie_insert.h"
#include "trie_remove.h"
#include "trie_find_coefficient.h"
#include "trie_paths.h"
#include "trie_monomials.h"

namespace po
{
  struct trie
  {
    using vertex = trie_vertex;

    std::size_t depth = 0;

    /*
     * A container for `vertex` instances.
     */
    std::vector<vertex> vertices;

    /*
     * An offset into `vertices` for each root vertex. The children of this vertex
     * are the roots of the prefix subtrees with distinct first values.
     */
    std::vector<std::size_t> roots;

    /*
     * Leaf coefficients
     */
    std::vector<scalar_type> coefficients;

    trie() = default;

    explicit trie(std::size_t _depth):
      depth(_depth)
    {}

    trie(std::initializer_list<monomial>&& _ilist):
      depth(_ilist.size() > 0 ? _ilist.begin()->exponents.size() : 0)
    {
      for(auto& m : _ilist)
      {
        auto mm = std::move(m);
        insert(std::move(mm.coefficient), std::move(mm.exponents));
      }
    }

    /*
     * Get the coefficient of the given exponents multiindex. If there is no such stored
     * multiindex, the coefficient is zero.
     */
    scalar_type coefficient(const po::exponents& exponents) const
    {
      return trie_coefficient(vertices, roots, coefficients, exponents);
    }

    /*
     * return: a path-wise iterable view of this trie.
     */
    trie_paths paths() const
    {
      return {depth, vertices, roots};
    }

    /*
     * return: an iterable view of the additive terms (monomials) in this trie.
     */
    trie_monomials monomials() const
    {
      return {depth, vertices, roots, coefficients};
    }

    /*
     * Get the number of paths in the tree. This includes any (virtually) deleted terms.
     */
    std::size_t npaths() const
    {
      return trie_npaths(coefficients);
    }

    /*
     * Get the number of terms in the polynomial represented here. This is equal
     * the number of logical paths in this instance.
     */
    std::size_t nterms() const
    {
      return trie_nterms(coefficients);
    }

    /*
     * Add the fields of a monomial term to the tree.
     */
    void insert(scalar_type&& c, po::exponents&& exponents)
    {
      trie_insert(vertices, roots, coefficients, std::move(c), std::move(exponents));
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

