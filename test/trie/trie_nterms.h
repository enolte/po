#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

#include "../../storage/trie/trie.h"

#include "../../ostream/trie_ostream.h"
#include "../../test/macros.h"

#include "utils.h"

#include "get_test_trie_rank7.h"

void trie_nterms_rank7();

void trie_nterms()
{
  trie_nterms_rank7();

  PO_LINE;
}

void trie_nterms_rank7()
{
  const std::size_t npaths = 10;
  po::trie t = get_test_trie_rank7(npaths);

  assert(t.npaths() == npaths);

  // std::stringstream ss;
  // ss << t;

  // PO_TRACE("t = " << ss.str());

  // ss = {};
  // get_paths(t, ss);

  // PO_TRACE("paths(t) before = " << std::endl << ss.str());

  assert(unique_coefficient_offsets(t.vertices));
  assert(t.npaths() == npaths);
  assert(t.nterms() == npaths);

  std::size_t k = npaths;
  std::size_t i = 0;
  while(k != 0)
  {
    if(k & 1)
      i = (i + t.npaths()) / 2;
    else
      i /= 2;

    t.remove({i/2, i/2 + 1, i, i + 1, i + 2, 2*i - i, 2*i});

    --k;
  }

  // ss = {};

  // ss << t;
  // PO_TRACE("t = " << ss.str());

  // ss = {};
  // get_paths(t, ss);

  // PO_TRACE("paths(t) after = " << std::endl << ss.str());
  // PO_TRACE("t.npaths() = " << t.npaths());
  // PO_TRACE("t.nterms() = " << t.nterms());

  assert(unique_coefficient_offsets(t.vertices));
  assert(t.npaths() == 10);
  assert(t.nterms() == 5);

}
