#ifndef PO_TRIE_PATHS_ITERATOR_H
#define PO_TRIE_PATHS_ITERATOR_H

#include "trie_path_index_iterator.h"

#include <functional>


namespace po
{
  /*
   * Convert a path child index into a sequence of vertex references.
   *
   * assumes: the trie is of uniform depth (current use case).
   */
  static std::vector<std::reference_wrapper<const trie_vertex>> get_path(
    const trie_path_index_iterator::index& vertex_index,
    const std::vector<trie_vertex>& vertices,
    const std::vector<std::size_t>& roots);


  struct trie_paths_iterator
  {
    // A sequence of vertex references. This is this iterator's value type.
    using vertex_path = std::vector<std::reference_wrapper<const trie_vertex>>;

    using iterator_category = trie_path_index_iterator::iterator_category;
    using value_type = vertex_path;
    using reference = const vertex_path&;
    using difference_type = void; // TODO Maybe: RandomAccessIterator concept
    using pointer = const vertex_path*;

    trie_path_index_iterator i;

    vertex_path path;

    reference operator*() const
    {
      return path;
    }

    pointer operator->() const
    {
      return &path;
    }

    trie_paths_iterator& operator++()
    {
      ++i;
      path = get_path(*i, i.m_vertices, i.m_roots);
      return *this;
    }
  };

  inline bool operator==(const trie_paths_iterator& i, const trie_paths_iterator& j)
  {
    return i.i == j.i;
  }

  inline bool operator!=(const trie_paths_iterator& i, const trie_paths_iterator& j)
  {
    return !(i == j);
  }

  /*
   * Convert a path child index into a sequence of vertex offsets.
   *
   * assumes: the trie is of uniform depth (current use case).
   */
  inline std::vector<std::reference_wrapper<const trie_vertex>> get_path(
    const trie_path_index_iterator::index& vertex_index,
    const std::vector<trie_vertex>& vertices,
    const std::vector<std::size_t>& roots)
  {
    if(vertex_index[0] == trie_constants::ABSENT)
    {
      // sentinel value for end state
      return {};
    }

    std::vector<std::reference_wrapper<const trie_vertex>> v;

    // Level 0 = offset of current root vertex
    std::size_t offset = roots[vertex_index[0]];

    v.push_back(std::cref(vertices[offset]));

    for(auto level{1zu}; level < vertex_index.size(); ++level)
    {
      offset = vertices[offset].children[vertex_index[level]];
      v.push_back(std::cref(vertices[offset]));
    }

    return v;
  }

}

#endif

