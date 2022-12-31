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

void trie_path_index_iterator_level_to_increment_rank3();

void trie_path_index_iterator_level_to_increment()
{
  trie_path_index_iterator_level_to_increment_rank3();

  PO_LINE;
}

void test_level_to_increment_root_rank3();
void test_level_to_increment_terminal_rank3();
void test_level_to_increment_non_terminal_rank3();


void trie_path_index_iterator_level_to_increment_rank3()
{
  test_level_to_increment_root_rank3();
  test_level_to_increment_terminal_rank3();
  test_level_to_increment_non_terminal_rank3();
}

void verify_level_to_increment(
  std::size_t level_to_increment,
  const std::vector<std::size_t>& index,
  const po::trie& t);

void test_level_to_increment_non_terminal_rank3()
{
  const po::trie t = get_test_trie_rank3();

  // write_trie_data_to_stdout(t);

  using I = po::trie_path_index_iterator;

  I::index index{0, 0, 2};

  const std::size_t level_to_increment = I::get_level_to_increment(index, t.vertices, t.roots);

  std::size_t offset;
  const po::trie::vertex& v = get_vertex_at_level(level_to_increment, offset, index, t);
  // PO_TRACE(" ** v = " << v);

  PO_ASSERT(level_to_increment == 1, level_to_increment);

  PO_ASSERT(
    index[level_to_increment] < v.children.size() - 1,
    index[level_to_increment]);
}

void test_level_to_increment_terminal_rank3()
{
  const po::trie t = get_test_trie_rank3();

  // write_trie_data_to_stdout(t);

  using I = po::trie_path_index_iterator;

  {
    I::index index(3);
    I::begin(index);
    PO_ASSERT((index == decltype(index){0, 0, 0}), index);

    const std::size_t level_to_increment = I::get_level_to_increment(index, t.vertices, t.roots);
    PO_ASSERT(level_to_increment == 2, level_to_increment);

    std::size_t offset;
    po::trie::vertex v = get_vertex_at_level(level_to_increment-1, offset, index, t);

    PO_ASSERT(
      index[level_to_increment] < v.children.size() - 1,
      index[level_to_increment]);

    v = t.vertices[v.children[index[level_to_increment-1]]];

    PO_ASSERT(is_terminal_vertex(v, t), v);
  }

  {
    I::index index{0, 0, 1};

    const std::size_t level_to_increment = I::get_level_to_increment(index, t.vertices, t.roots);
    PO_ASSERT(level_to_increment == 2, level_to_increment);

    std::size_t offset;
    po::trie::vertex v = get_vertex_at_level(level_to_increment-1, offset, index, t);

    PO_ASSERT(
      index[level_to_increment] < v.children.size() - 1,
      index[level_to_increment]);

    v = t.vertices[v.children[index[level_to_increment-1]]];

    PO_ASSERT(is_terminal_vertex(v, t), v);
  }

}


void test_level_to_increment_root_rank3()
{
  const po::trie t = get_test_trie_rank3();

  // write_trie_data_to_stdout(t);

  using I = po::trie_path_index_iterator;

  const I::index index{0, 1, 0};

  const std::size_t level_to_increment = I::get_level_to_increment(index, t.vertices, t.roots);

  std::size_t offset;
  const po::trie::vertex& v = get_vertex_at_level(level_to_increment, offset, index, t);
  // PO_TRACE(" ** v = " << v);

  PO_ASSERT(level_to_increment == 0, level_to_increment);

  verify_level_to_increment(level_to_increment, index, t);

}



// Verify that level_to_increment is the lowest level than can be incremented.
void verify_level_to_increment(std::size_t level_to_increment, const std::vector<std::size_t>& index, const po::trie& t)
{
  using I = po::trie_path_index_iterator;

  std::size_t offset;
  get_vertex_at_level(level_to_increment, offset, index, t);

  std::size_t level = level_to_increment+1;
  offset = t.vertices[offset].children[index[level]];
  po::trie::vertex v = t.vertices[offset];
  while(!is_terminal_vertex(v, t))
  {
    // PO_TRACE(" ** level = " << level);
    // PO_TRACE(" **  index[" << level+1 << "] = " << index[level+1]);
    // PO_TRACE(" **  offset = " << offset);
    // PO_TRACE(" **  v = " << v);
    // PO_TRACE(" **  v.children.size() = " << v.children.size());

    PO_ASSERT(index[level+1] == v.children.size() - 1, level);

    ++level;
    offset = t.vertices[offset].children[index[level]];
    v = t.vertices[offset];
  }
}
