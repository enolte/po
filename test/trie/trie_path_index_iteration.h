#include <iostream>
#include <cassert>

#include "../../test/macros.h"
#include "../../storage/trie/trie_path_index_iterator.h"

#include "utils.h"
#include "get_test_trie_rank3.h"

using po::operator<<;

void trie_path_index_iteration()
{
  po::trie t = get_test_trie_rank3();

  po::trie_path_index_iterator i(t.vertices, t.roots, t.depth);

  // std::cout << " ** path index = " << *i << std::endl;
  PO_ASSERT((*i == (decltype(*i)){0, 0, 0}), *i);

  ++i;
  // std::cout << " ** path index = " << *i << std::endl;
  PO_ASSERT((*i == (decltype(*i)){0, 0, 1}), *i);

  ++i;
  // std::cout << " ** path index = " << *i << std::endl;
  PO_ASSERT((*i == (decltype(*i)){0, 0, 2}), *i);

  ++i;
  // std::cout << " ** path index = " << *i << std::endl;
  PO_ASSERT((*i == (decltype(*i)){0, 1, 0}), *i);

  ++i;
  // std::cout << " ** path index = " << *i << std::endl;
  PO_ASSERT((*i == (decltype(*i)){1, 0, 0}), *i);

  // If at last, transition to end state
  ++i;
  // std::cout << " ** path index = " << *i << std::endl;
  PO_ASSERT((*i == (decltype(*i)){po::trie_constants::ABSENT, 0, 0}), *i);

  // End state is idempotent.
  ++i;
  // std::cout << " ** path index = " << *i << std::endl;
  PO_ASSERT((*i == (decltype(*i)){po::trie_constants::ABSENT, 0, 0}), *i);

  PO_LINE;
}


