#include <iostream>
#include <cassert>

#include "../../test/macros.h"
#include "../../storage/trie/trie_paths.h"

#include "utils.h"
#include "get_test_trie_rank3.h"

using po::operator<<;

void trie_paths_iterator_next_rank3();

void trie_paths_iterator_next()
{
  trie_paths_iterator_next_rank3();

  PO_LINE;
}

void trie_paths_iterator_next_rank3()
{
  const po::trie t = get_test_trie_rank3();
  po::trie_paths paths{t.depth, t.vertices, t.roots};

  po::trie_paths::const_iterator i = paths.cbegin();

  ++i;
  // std::cout << " ** path = " << *i << std::endl;

  PO_ASSERT(i->size() == t.depth, i->size());
  PO_ASSERT(i == ++paths.cbegin(), *i);
}