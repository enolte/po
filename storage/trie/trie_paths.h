#ifndef PO_TRIE_PATHS_H
#define PO_TRIE_PATHS_H

#include "trie_paths_iterator.h"

namespace po
{

  /*
   * A const view of the trie as an iterable sequence of vertex paths.
   */
  struct trie_paths
  {
    using const_iterator = po::trie_paths_iterator;

    const std::size_t m_depth;
    const std::vector<trie_vertex>& m_vertices;
    const std::vector<std::size_t>& m_roots;

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
      const_iterator i{{m_vertices, m_roots, m_depth}, {}};
      i.path = get_path(*(i.i), m_vertices, m_roots);
      return i;
    }

    const_iterator cend() const
    {
      return {{m_vertices, m_roots, m_depth, true}, {}};
    }
  };

}

#endif

