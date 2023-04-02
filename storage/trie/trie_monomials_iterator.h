#ifndef PO_TRIE_MONOMIALS_ITERATOR_H
#define PO_TRIE_MONOMIALS_ITERATOR_H

#include "trie_path_index_iterator.h"

#include "../../types/monomial.h"

namespace po
{
  /*
   * Convert a path child index into a monomial.
   *
   * assumes: the trie is of uniform depth (current use case).
   */
  static po::monomial get_monomial(
    const trie_path_index_iterator::index& vertex_index,
    const std::vector<trie_vertex>& vertices,
    const std::vector<std::size_t>& roots,
    const std::vector<scalar_type>& coefficients);

  struct trie_monomials_iterator
  {



    using iterator_category = trie_path_index_iterator::iterator_category;
    using value_type = po::monomial;
    using reference = const value_type&;
    using difference_type = void; // TODO Maybe: RandomAccessIterator concept
    using pointer = const value_type*;

    trie_path_index_iterator i;
    const std::vector<scalar_type>& m_coefficients;
    po::monomial term;

    reference operator*() const
    {
      return term;
    }

    pointer operator->() const
    {
      return &term;
    }

    trie_monomials_iterator& operator++()
    {
      do
      {
        ++i;
        term = get_monomial(*i, i.m_vertices, i.m_roots, m_coefficients);
      } while(term.coefficient != term.coefficient);
      return *this;
    }
  };

  inline bool operator==(const trie_monomials_iterator& i, const trie_monomials_iterator& j)
  {

    return i.i == j.i;
  }

  inline bool operator!=(const trie_monomials_iterator& i, const trie_monomials_iterator& j)
  {
    return !(i == j);
  }

  /*
   * Convert a path child index into a multiindex.
   *
   * assumes: the trie is of uniform depth (current use case).
   */
  inline po::monomial get_monomial(
    const trie_path_index_iterator::index& vertex_index,
    const std::vector<trie_vertex>& vertices,
    const std::vector<std::size_t>& roots,
    const std::vector<scalar_type>& coefficients)
  {
    if(vertex_index[0] == trie_constants::ABSENT)
    {
      // sentinel value for end state
      return {};
    }

    po::monomial monomial{
       trie_constants::absent_value,
       po::exponents(trie_constants::ABSENT, vertex_index.size())};

    // Level 0 = offset of current root vertex
    std::size_t offset = roots[vertex_index[0]];

    monomial.exponents[0] = vertices[offset].value;

    for(auto level{1zu}; level < vertex_index.size(); ++level)
    {
      offset = vertices[offset].children[vertex_index[level]];
      monomial.exponents[level] = vertices[offset].value;
    }

    offset = vertices[offset].children[0];
    const std::size_t coefficient_offset = vertices[offset].value;

    monomial.coefficient = coefficients[coefficient_offset];

    return monomial;
  }

}

#endif

