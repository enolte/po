#include <iostream>
#include <cassert>

#include "../../test/macros.h"
#include "../../storage/trie/trie_paths.h"

#include "utils.h"
#include "get_test_trie_rank3.h"

using po::operator<<;

void trie_paths_get_vertices_rank3();

void trie_paths_get_vertices()
{
  trie_paths_get_vertices_rank3();

  PO_LINE;
}

void trie_paths_get_vertices_rank3()
{
  // PO_TRACE("────────────────────────────────────────────────────────────────");
  // PO_FUNC;

  const po::trie t = get_test_trie_rank3();
  po::trie_paths paths{t.depth, t.vertices, t.roots};

  po::trie_paths::const_iterator i = paths.cbegin();

  // std::cout << " ** path = " << *i << std::endl;

  PO_ASSERT(i->size() == t.depth, i->size());
  PO_ASSERT(i == paths.cbegin(), *i);

  ++i;
  PO_ASSERT(
    (*i == po::trie_paths::const_iterator::value_type
      {
        t.vertices[0], t.vertices[1], t.vertices[4]
      }),
    *i);

  ++i;
  PO_ASSERT(
    (*i == po::trie_paths::const_iterator::value_type
      {
        t.vertices[0], t.vertices[1], t.vertices[6]
      }),
    *i);

/*

  I::index index(3);
  I::begin(index);

  PO_ASSERT((index == (decltype(index)){0, 0, 0}), index);

  I::next(index, t.vertices, t.roots);
  PO_ASSERT((index == (decltype(index)){0, 0, 1}), index);

  auto p = I::get_vertices(index, t.vertices, t.roots);

  std::cout << " ** p = " << p << std::endl;

  PO_ASSERT((p[0] == po::trie_vertex{3, {1, 8}})   , p[0]);
  PO_ASSERT((p[1] == po::trie_vertex{5, {2, 4, 6}}), p[1]);
  PO_ASSERT((p[2] == po::trie_vertex{5, {5}})      , p[2]);
  assert(is_terminal_vertex(p[2], t));


  I::next(index, t.vertices, t.roots);
  PO_ASSERT((index == (decltype(index)){0, 0, 2}), index);

  p = I::get_vertices(index, t.vertices, t.roots);

  std::cout << " ** p = " << p << std::endl;

  PO_ASSERT((p[0] == po::trie_vertex{3, {1, 8}})   , p[0]);
  PO_ASSERT((p[1] == po::trie_vertex{5, {2, 4, 6}}), p[1]);
  PO_ASSERT((p[2] == po::trie_vertex{2, {7}})      , p[2]);
  assert(is_terminal_vertex(p[2], t));

  I::next(index, t.vertices, t.roots);
  PO_ASSERT((index == (decltype(index)){0, 1, 0}), index);

  p = I::get_vertices(index, t.vertices, t.roots);

  std::cout << " ** p = " << p << std::endl;

  PO_ASSERT((p[0] == po::trie_vertex{3, {1, 8}})   , p[0]);
  PO_ASSERT((p[1] == po::trie_vertex{3, {9}})      , p[1]);
  PO_ASSERT((p[2] == po::trie_vertex{6, {10}})     , p[2]);
  assert(is_terminal_vertex(p[2], t));
*/
}



