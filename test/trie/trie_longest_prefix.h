#include <iostream>
#include <cassert>
#include <vector>

#include "../../ostream/trie_vertex_ostream.h"
#include "../../test/macros.h"

#include "../../storage/trie/trie_longest_prefix.h"

using po::operator<<;

void trie_longest_prefix()
{
  {
    /*
    paths:
      1 5
      1 4
      2 5

      (x) exponent=1                                   (x) exponent = 2
       |                                                |
       +---------------------------+                    |
       |                           |                    |
       v                           v                    v
      (y) exponent=5              (y) exponent=4        (y) exponent = 5
    */
    const std::vector<po::trie_vertex> v
    {
      {1, {2, 3}}, // 0
      {2, {2}},    // 1
      {5, {}},     // 2
      {4, {}},     // 3
    };

    const auto [last_vertex, length] = po::trie_longest_prefix(
      v,
      {0, 1},  // roots
      {1, 0}); // exponents


    assert(length == 1);
    assert(last_vertex == 0);
  }

  {
    /*
    paths:
      1 5
      1 4 7
      1 4 2
      2 5
    */
    const std::vector<po::trie_vertex> v
    {
      {1, {2, 3}},    // 0
      {2, {2}},       // 1
      {5, {}},        // 2
      {4, {4, 5}},    // 3
      {7, {}},        // 4
      {2, {}},        // 5
    };


    const auto [last_vertex, length] = po::trie_longest_prefix(
      v,
      {0, 1},  // roots
      {1, 4}); // exponents


    assert(length == 2);
    assert(last_vertex == 3);
  }

  {
    /*
    paths:
      1 5
      1 4 7
      1 4 2
      2 5
    */
    const std::vector<po::trie_vertex> v
    {
      {1, {2, 3}},    // 0
      {2, {2}},       // 1
      {5, {}},        // 2
      {4, {4, 5}},    // 3
      {7, {}},        // 4
      {2, {}},        // 5
    };



    const auto [last_vertex, length] = po::trie_longest_prefix(
      v,
      {0, 1},     // roots
      {1, 4, 6}); // exponents


    assert(length == 2);
    assert(last_vertex == 3);
  }

  {

    /*
     paths:

     1 5
     1 4 7 1
     1 4 2
     2 5
    */
    const std::vector<po::trie_vertex> v
    {
      {1, {2, 3}},    // 0
      {2, {2}},       // 1
      {5, {}},        // 2
      {4, {4, 5}},    // 3
      {7, {6}},       // 4
      {2, {}},        // 5
      {1, {}},        // 6
    };


    const auto [last_vertex, length] = po::trie_longest_prefix(
      v,
      {0, 1},     // roots
      {1, 4, 3}); // exponents


    assert(length == 2);
    assert(last_vertex == 3);
  }

  {
    const std::vector<std::size_t> roots
    {
      0, 11
    };

    const std::vector<po::trie_vertex> vertices
    {
      {3, {1, 7}},    //  0
      {5, {2}},       //  1
      {2, {3, 5}},    //  2
      {4, {4}},       //  3
      {0, {}},        //  4 coefficient offset
      {1, {6}},       //  5
      {1, {}},        //  6 coefficient offset
      {4, {8}},       //  7
      {3, {9}},       //  8
      {2, {10}},      //  9
      {2, {}},        // 10 coefficient offset
      {7, {12, 16}},  // 11
      {4, {13}},      // 12
      {3, {14}},      // 13
      {6, {15}},      // 14
      {3, {}},        // 15 coefficient offset
      {1, {17}},      // 16
      {3, {18}},      // 17
      {6, {19}},      // 18
      {4, {}},        // 19 coefficient offset
    };

    /*
    paths        coefficient offsets

      3 5 2 4      0
      3 5 2 1      1
      3 4 3 2      2
      7 4 3 6      3
      7 1 3 6      4
    */

    const auto [last_vertex, length] = po::trie_longest_prefix(vertices, roots, {7, 4, 3, 6});
    PO_ASSERT(length == 4, length);
    PO_ASSERT(last_vertex == 14, last_vertex);
    assert(vertices[last_vertex].children.size() == 1);

  }

  PO_LINE;
}
