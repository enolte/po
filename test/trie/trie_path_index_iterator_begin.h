#include <iostream>
#include <cassert>
#include <vector>

#include "../../ostream/valarray_ostream.h"
#include "../../ostream/trie_vertex_ostream.h"
#include "../../test/macros.h"

#include "../../storage/trie/trie_path_index_iterator.h"

#include "utils.h"

#include "get_test_trie_rank3.h"

using po::operator<<;

void trie_path_index_iterator_begin_rank3();

void trie_path_index_iterator_begin()
{
  trie_path_index_iterator_begin_rank3();

  PO_LINE;
}

void trie_path_index_iterator_begin_rank3()
{
  const po::trie t = get_test_trie_rank3();

  using I = po::trie_path_index_iterator;

  I::index path_index(3);
  I::begin(path_index);

  PO_ASSERT((path_index == (decltype(path_index)){0, 0, 0}), path_index);
}



