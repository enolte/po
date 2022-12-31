#include <iostream>
#include <cassert>

#include "../../test/macros.h"
#include "../../storage/trie/trie_npaths.h"

#include "utils.h"
#include "get_test_trie_rank3.h"
#include "get_test_trie_rank5.h"

using po::operator<<;

void trie_npaths_rank3();
void trie_npaths_rank5();

void trie_npaths()
{
  trie_npaths_rank3();
  trie_npaths_rank5();

  PO_LINE;
}

void trie_npaths_rank3()
{
  po::trie t = get_test_trie_rank3();

  assert(t.npaths() == 5);
}

void trie_npaths_rank5()
{
  po::trie t = get_test_trie_rank5();

  assert(t.npaths() == 6);
}
