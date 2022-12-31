#include <iostream>
#include <cassert>

#include "../../test/macros.h"

#include "../../storage/trie/trie_path_index_iterator.h"

#include "utils.h"

#include "get_test_trie_rank3.h"

using po::operator<<;

void trie_path_index_iterator_ctor()
{
  po::trie t{3};
  po::trie_path_index_iterator i(t.vertices, t.roots, t.depth);

  static_assert(std::same_as<decltype(*i), const po::trie_path_index_iterator::index&>);

  assert(i->size() == 3);
  assert(i->size() == t.depth);
  assert((*i).size() == t.depth);
  assert(i->data() == i.m_vertex_index.data());

  PO_ASSERT((*i == (decltype(*i)){0, 0, 0}), *i);

  PO_LINE;
}


