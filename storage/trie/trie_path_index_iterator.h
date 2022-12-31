#ifndef PO_TRIE_PATH_INDEX_ITERATOR_H
#define PO_TRIE_PATH_INDEX_ITERATOR_H

#include "trie_vertex.h"

#include <algorithm>
#include <iterator>

namespace po
{
  /*
   * Implementor for a full path DFS iterator for a trie instance. Only full paths are iterated. Each path
   * terminates with a vertex which has exactly one child, which is a leaf.
   *
   * That child's value field is the offset of the term coefficient into the trie's
   * coefficient sequence.
   *
   * The use case for this implementaion is a trie of uniform depth. This implementation
   * makes use of that fact for optimization.
   */
  struct trie_path_index_iterator
  {
    // The index component at offset L is an offset into the array of child offsets for the vertex
    // at level L-1. This identifies the vertex at level L in terms of the children at level L-1.
    using index = std::vector<std::size_t>;

    using iterator_category = std::forward_iterator_tag;
    using value_type = index;
    using reference = const index&;
    using difference_type = void; // TODO Maybe: RandomAccessIterator concept
    using pointer = const index*;

  private:
  // TODO Should be private. Pending.
  public:
    /*
     * TODO N.B. Using references here disables `std::ranges` algorithms.
     *
     * These fields prevent this type from satisfying the `std::input_or_output_iterator` concept,
     * because this type is not default-contructible as it is.
     *
     * This causes template resolution of `std::ranges` algorithms to fail, with unsatisfied constraints.
     *
     * The workaround is not to use `std::ranges`, which is undesirable. The real solution to this
     * problem is to refactor this type to be default-constructible.
     */
    const std::vector<trie_vertex>& m_vertices;
    const std::vector<std::size_t>& m_roots;

    /*
     * For i = m_vertex_index[n],
     *
     *   If n > 0, i is an offset into the children of the vertex, v, at level n-1 on
     *   the current path. The vertex at level n in the current path is v.children[i],
     *   which is v.children[vertex_index[n]]. If n = 1, then v (at level 0) is a root.
     *
     *   If n = 0, i is the offset of the root vertex. The root vertex is
     *   vertices[roots[i]] = vertices[roots[vertex_index[0]]]
     */
    index m_vertex_index;

  public:
    trie_path_index_iterator(
      const std::vector<trie_vertex>& _vertices,
      const std::vector<std::size_t>& _roots,
      std::size_t _depth,
      bool end = false):
      m_vertices(_vertices),
      m_roots(_roots),
      m_vertex_index(_depth, 0)
    {
      if(end)
        m_vertex_index[0] = trie_constants::ABSENT;
    }

    /*
     * Pre-increment.
     */
    trie_path_index_iterator& operator++()
    {
      next(m_vertex_index, m_vertices, m_roots);
      return *this;
    }

    /*
     * Post-increment. (Why does anyone use this pattern for iteration?)
     */
    // TODO Test
    trie_path_index_iterator operator++(int)
    {
      trie_path_index_iterator i{*this};
      next(m_vertex_index, m_vertices, m_roots);
      return i;
    }

    reference operator*() const
    {
      return m_vertex_index;
    }

    pointer operator->() const
    {
      return &m_vertex_index;
    }

    /*
     * Get the first path.
     *
     * assumes: vertex_index.size() >= trie rank
     * assumes: the trie is of uniform depth (current use case)
     */
    static void begin(index& vertex_index)
    {
      std::fill(vertex_index.begin(), vertex_index.end(), 0);
    }

    /*
     * Find the level L for which the child index is to be incremented. This value
     * is stored in the index of the parent, at level L-1.
     *
     * This is used to change the value of vertex_index[L]. L is the level number of the last
     * vertex on the path which has a forward sibling.
     *
     * assumes: vertex_index.size() == trie rank
     * assumes: the trie is of uniform depth (current use case)
     */
    static std::size_t get_level_to_increment(
      const index&,
      const std::vector<trie_vertex>& vertices,
      const std::vector<std::size_t>& roots);

    /*
     * Set the current path to the left-most path beneath the current path vertex
     * at the given level. If level == 0, this sets the path beginning with a child
     * of the root@entry.
     *
     * assumes: vertex_index.size() >= trie rank
     * assumes: the trie is of uniform depth (current use case)
     */
    static void set_first_path(std::size_t level, index& vertex_index)
    {
      std::fill(vertex_index.begin() + (level+1), vertex_index.end(), 0);
    }

    /*
     * For child vertex index, c,
     *  c[0] = offset into the `roots` index
     *  c[i] = offset into the `children` index of the previous vertex, for i > 0
     *
     * I.e., a path traversal induces a sequence, n_i, of vertex storage offsets as
     *  n_0 = roots[c[0]]
     *  n_1 = vertices[n_0].children[c[1]]
     *  n_2 = vertices[n_1].children[c[2]]
     *  n_3 = vertices[n_2].children[c[3]]
     *  ...
     *
     * The ith path vertex v_i is then vertices[n_i].
     *
     * The `roots` index is the children index of the (virtual)
     * trie root vertex, implemented by the trie object itself.
     *
     * assumes: vertex_index.size() == trie rank
     * assumes: the trie is of uniform depth (current use case)
     *
     * return: true iff there is a next path in the trie. In that case, the vertex holds
     *         the resulting next path. If the return value value is false, the vertex index
     *         is unchanged.
     *
     */
    static bool next(
      index&,
      const std::vector<trie_vertex>& vertices,
      const std::vector<std::size_t>& roots);
  };

  inline bool trie_path_index_iterator::next(
    index& vertex_index,
    const std::vector<trie_vertex>& vertices,
    const std::vector<std::size_t>& roots)
  {
    if(vertex_index[0] == trie_constants::ABSENT)
      return false;

    const std::size_t level_to_increment = get_level_to_increment(vertex_index, vertices, roots);

    if(level_to_increment == 0)
    {
      if(roots.size() == vertex_index[0] + 1)
      {
        // sentinel value for end state
        vertex_index[0] = trie_constants::ABSENT;
        return false;
      }
    }

    ++vertex_index[level_to_increment];

    set_first_path(level_to_increment, vertex_index);

    return true;
  }

  /*
   * Find the level L for which the child index is to be incremented. This value
   * is stored in the index of the parent, at level L-1.
   *
   * This is used to change the value of vertex_index[L]. L is the level number of the last
   * vertex on the path which has a forward sibling.
   *
   * assumes: the trie is of uniform depth (current use case).
   */
  inline std::size_t trie_path_index_iterator::get_level_to_increment(
    const index& vertex_index,
    const std::vector<trie_vertex>& vertices,
    const std::vector<std::size_t>& roots)
  {
    // Level 0 = offset of current root vertex
    std::size_t offset = roots[vertex_index[0]];

    std::size_t last_incrementable_level = 0;
    for(auto level{1zu}; level < vertex_index.size(); ++level)
    {
      if(vertex_index[level] + 1 < vertices[offset].children.size())
      {
        last_incrementable_level = level;
      }

      offset = vertices[offset].children[vertex_index[level]];
    }

    return last_incrementable_level;
  }

  inline bool operator==(const trie_path_index_iterator& i, const trie_path_index_iterator& j)
  {
    // return ((*i)[0] == (*j)[0] && (*j)[0] == trie_constants::ABSENT) || *i == *j;
    return *i == *j;
  }

  inline bool operator!=(const trie_path_index_iterator& i, const trie_path_index_iterator& j)
  {
    return !(i == j);
  }


#if 0
  /*
   * Convert a path child index into a sequence of vertex offsets.
   *
   * assumes: the trie is of uniform depth (current use case).
   */
  // TODO Test
  inline std::vector<std::size_t> get_vertex_offsets(
    const index& vertex_index,
    const std::vector<trie_vertex>& vertices,
    const std::vector<std::size_t>& roots)
  {
    std::vector<std::size_t> offsets(vertex_index.size());
    offsets[0] = roots[vertex_index[0]];

    for(auto level{1zu}; level < vertex_index.size(); ++level)
    {
      offsets[level] = vertices[offsets[level-1]].children[vertex_index[level]];
    }

    return offsets;
  }
#endif

}


#endif

