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

void trie_path_index_iterator_set_first_path_rank3();

void trie_path_index_iterator_set_first_path()
{
  trie_path_index_iterator_set_first_path_rank3();

  PO_LINE;
}

void test_set_first_path_rank3();
void test_set_first_path_from_root_rank3();
void test_set_first_path_from_terminal_rank3();
void test_set_first_path_from_nonterminal_rank3();

void trie_path_index_iterator_set_first_path_rank3()
{
  test_set_first_path_rank3();
  test_set_first_path_from_root_rank3();
  test_set_first_path_from_terminal_rank3();
  test_set_first_path_from_nonterminal_rank3();
}

void test_set_first_path_rank3()
{
  const po::trie t = get_test_trie_rank3();

  // write_trie_data_to_stdout(t);

  using I = po::trie_path_index_iterator;

  {
    I::index index(3);
    I::begin(index);

    // Intermediate state: Choose a different path in the test trie: 0, 0, 2.
    // Then advance index[1] to be the next child of level 0.
    index[1] = 1;
    index[2] = 2;

    assert((index == decltype(index){0, 1, 2}));

    I::set_first_path(1, index);

    PO_ASSERT((index == decltype(index){0, 1, 0}), index);
  }
}

void test_set_first_path_from_root_rank3()
{
  const po::trie t = get_test_trie_rank3();

  // write_trie_data_to_stdout(t);

  using I = po::trie_path_index_iterator;

  I::index index{1, 1, 0};

  I::set_first_path(0, index);

  PO_ASSERT((index == decltype(index){1, 0, 0}), index);
}

void test_set_first_path_from_nonterminal_rank3()
{
  const po::trie t = get_test_trie_rank3();

  // write_trie_data_to_stdout(t);

  using I = po::trie_path_index_iterator;

  I::index index{0, 0, 2};

  I::set_first_path(1, index);

  PO_ASSERT((index == decltype(index){0, 0, 0}), index);
}


void test_set_first_path_from_terminal_rank3()
{
  const po::trie t = get_test_trie_rank3();

  // write_trie_data_to_stdout(t);

  using I = po::trie_path_index_iterator;

  I::index index{0, 0, 2};

  I::set_first_path(2, index);

  PO_ASSERT((index == decltype(index){0, 0, 2}), index);
}
