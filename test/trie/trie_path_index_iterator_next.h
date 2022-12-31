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

void trie_path_index_iterator_next_rank3();
void trie_path_index_iterator_post_incr_rank3();

void trie_path_index_iterator_next()
{
  trie_path_index_iterator_next_rank3();
  trie_path_index_iterator_post_incr_rank3();

  PO_LINE;
}

void test_next_rank3();


void trie_path_index_iterator_post_incr_rank3()
{
  const po::trie t = get_test_trie_rank3();

  using I = po::trie_path_index_iterator;

  I i = I{t.vertices, t.roots, t.depth};

  I i_prev = i;
  PO_ASSERT(i_prev == i++, *i_prev);
  PO_ASSERT(i_prev != i, *i_prev);
  PO_ASSERT(i_prev++ != i, *i_prev);
  PO_ASSERT(i_prev == i, *i_prev);
  PO_ASSERT(i != i++, *i);
}

void trie_path_index_iterator_next_rank3()
{
  test_next_rank3();
}

void test_next_rank3()
{
  const po::trie t = get_test_trie_rank3();

  using I = po::trie_path_index_iterator;

  I::index index(3);
  I::begin(index);
  // std::cout << " ** path index = " << index << std::endl;
  PO_ASSERT((index == (decltype(index)){0, 0, 0}), index);

  I::next(index, t.vertices, t.roots);
  // std::cout << " ** path index = " << index << std::endl;
  PO_ASSERT((index == (decltype(index)){0, 0, 1}), index);

  I::next(index, t.vertices, t.roots);
  // std::cout << " ** path index = " << index << std::endl;
  PO_ASSERT((index == (decltype(index)){0, 0, 2}), index);

  I::next(index, t.vertices, t.roots);
  // std::cout << " ** path index = " << index << std::endl;
  PO_ASSERT((index == (decltype(index)){0, 1, 0}), index);

  I::next(index, t.vertices, t.roots);
  // std::cout << " ** path index = " << index << std::endl;
  PO_ASSERT((index == (decltype(index)){1, 0, 0}), index);

  // If at last, transition to end state.
  bool has_next = I::next(index, t.vertices, t.roots);
  assert(!has_next);
  // std::cout << " ** path index = " << index << std::endl;

  // Change to end state.
  PO_ASSERT((index == (decltype(index)){po::trie_constants::ABSENT, 0, 0}), index);

  // End state is idempotent.
  has_next = I::next(index, t.vertices, t.roots);
  assert(!has_next);
  // std::cout << " ** path index = " << index << std::endl;

  PO_ASSERT((index == (decltype(index)){po::trie_constants::ABSENT, 0, 0}), index);

  // TODO Maybe circular instead.
/*
  // Circular iteration: next after end is begin
  has_next = I::next(index, t);
  assert(has_next);
  std::cout << " ** path index = " << index << std::endl;
  I::index begin(3);
  I::begin(begin, t);

  PO_ASSERT(begin == index, index);
*/

}

