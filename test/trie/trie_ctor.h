#include <iostream>
#include <cassert>

#include "../../test/macros.h"
#include "../../storage/trie/trie.h"

#include "utils.h"
#include "get_test_trie_rank3.h"

using po::operator<<;

void trie_ctor()
{
  {
    po::trie t;

    PO_ASSERT(t.vertices.size() == 0, t.vertices);
    PO_ASSERT(t.roots.size() == 0, t.roots);
    PO_ASSERT(t.coefficients.size() == 0, t.coefficients);
    PO_ASSERT(t.depth == 0, t.depth);
  }

  {
    po::trie t{3};

    PO_ASSERT(t.vertices.size() == 0, t.vertices);
    PO_ASSERT(t.roots.size() == 0, t.roots);
    PO_ASSERT(t.coefficients.size() == 0, t.coefficients);
    PO_ASSERT(t.depth == 3, t.depth);
  }

  {
    const po::trie t
    {
      {4.7, {2, 3, 4, 5}},
      {0.3, {2, 4, 5, 6}},
      {1.1, {2, 3, 5, 7}},
    };

    PO_ASSERT(t.vertices.size() == 12, t.vertices);
    PO_ASSERT(t.roots.size() == 1, t.roots);
    PO_ASSERT(t.coefficients.size() == 3, t.coefficients);
    PO_ASSERT(t.depth == 4, t.depth);
  }

  PO_LINE;
}


