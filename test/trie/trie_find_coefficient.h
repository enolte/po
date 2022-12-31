#include <iostream>
#include <cassert>
#include <vector>

#include "../../ostream/trie_vertex_ostream.h"
#include "../../test/macros.h"

#include "../../storage/trie/trie_find_coefficient.h"
#include "../../storage/trie/trie_insert.h"

using po::operator<<;

void trie_find_coefficient()
{
  std::vector<po::trie_vertex> vertices;
  std::vector<std::size_t> roots;
  std::vector<po::scalar_type> coefficients;

  trie_insert(vertices, roots, coefficients, 1., {3, 5, 2, 4});
  trie_insert(vertices, roots, coefficients, 2., {3, 5, 2, 1});
  trie_insert(vertices, roots, coefficients, 3., {3, 4, 3, 2});
  trie_insert(vertices, roots, coefficients, 4., {7, 4, 3, 6});
  trie_insert(vertices, roots, coefficients, 5., {7, 1, 3, 6});

  {
    const std::size_t c_offset = trie_find_coefficient(vertices, roots, {7, 4, 3, 6});
    PO_ASSERT(c_offset == 3, c_offset);

    assert(coefficients[c_offset] == 4.);
  }

  {
    const std::size_t c_offset = trie_find_coefficient(vertices, roots, {7, 9, 3, 6});
    PO_ASSERT(c_offset == po::trie_constants::ABSENT, c_offset);
  }

  PO_LINE;
}

