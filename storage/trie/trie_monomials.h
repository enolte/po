#ifndef PO_TRIE_MONOMIALS_H
#define PO_TRIE_MONOMIALS_H

#include "trie_monomials_iterator.h"

namespace po
{
  // TODO Test
  struct trie_monomials
  {
    using iterator = po::trie_monomials_iterator;
    using const_iterator = iterator;

    const std::size_t m_depth;

    const std::vector<trie_vertex>& m_vertices;
    const std::vector<std::size_t>& m_roots;
    const std::vector<scalar_type>& m_coefficients;

    const_iterator begin() const
    {
      return cbegin();
    }

    const_iterator end() const
    {
      return cend();
    }

    const_iterator cbegin() const
    {
      const_iterator i{{m_vertices, m_roots, m_depth}, m_coefficients, {}};
      i.term = get_monomial(*(i.i), m_vertices, m_roots, m_coefficients);
      return i;
    }

    const_iterator cend() const
    {
      return {{m_vertices, m_roots, m_depth, true}, m_coefficients, {}};
    }
  };

}

#endif

