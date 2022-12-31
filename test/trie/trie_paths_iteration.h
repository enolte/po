#include <iostream>
#include <cassert>

#include "../../test/macros.h"
#include "../../storage/trie/trie_paths.h"

#include "utils.h"
#include "get_test_trie_rank3.h"

using po::operator<<;


void trie_paths_iteration_rank3();

void trie_paths_iteration()
{
  trie_paths_iteration_rank3();

  PO_LINE;
}

void trie_paths_iteration_rank3()
{
  po::trie t = get_test_trie_rank3();

  int k = -1;
  auto i = t.paths().cbegin();
  for(; i != t.paths().cend(); ++i)
  {
    ++k;
    // std::cout << " ** path = " << *i << "  ,  index = " << *i.i << std::endl;
  }

  // std::cout << " ** path = " << *i << "  ,  index = " << *i.i << std::endl;

  assert(k == t.coefficients.size() - 1);

  k = -1;
  const auto paths = t.paths();
  for(const auto& path : paths)
  {
    ++k;
    // std::cout << " ** [" << k << "] path = " << path << std::endl;
  }

  assert(k == t.coefficients.size() - 1);

  k = -1;
  for(const auto& path : t.paths())
  {
    ++k;
    // std::cout << " ** [" << k << "] path = " << path << std::endl;
  }

  assert(k == t.coefficients.size() - 1);
}

#include <algorithm>


// TODO
#if 0
void trie_paths_iteration_ranges_rank3()
{
  po::trie t = get_test_trie_rank3();

  static_assert(std::input_or_output_iterator<po::trie_paths::iterator>);

  static_assert(std::ranges::range<po::trie_paths>);

  const auto begin = std::ranges::begin(t.paths());
  const auto end = std::ranges::end(t.paths());

  std::size_t k = 0;
  std::ranges::for_each(
    t.paths(),
    [&k](const auto&) { ++k; });

  assert(k == t.coefficients.size());

  k = 0;
  std::ranges::for_each(
    t.paths(),
    [&k](const po::trie_paths::iterator::value_type&) { ++k; });

  assert(k == t.coefficients.size());
}
#endif



