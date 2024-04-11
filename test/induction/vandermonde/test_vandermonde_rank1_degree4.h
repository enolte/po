#include <iostream>
#include <cassert>
#include "../../macros.h"

#include "../timed_construct.h"

namespace po_test
{
  void test_vandermonde_rank1_degree4()
  {
    // Knot points, stored in rows here
    static constexpr double p[][2]
    {
      {0},
      {1},
      {2},
      {3},
      {4},
    };

    // Select knot points by column
    static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };

    auto v = po_test::vandermonde::timed_construct(f, 1, 4);

    PO_ASSERT(v.nrows == 5, v.nrows);
    PO_ASSERT(v.ncols == 5, v.ncols);
    PO_ASSERT(
      equal(
        v.data,
        {                                     // row multiindices
          1,     1,     1,     1,     1,      // 0
          0,     1,     2,     3,     4,      // 1
          0,     1,     4,     9,    16,      // 2
          0,     1,     8,    27,    64,      // 3
          0,     1,    16,    81,   256,      // 4
        }),
      v);

    PO_LINE;
  }

}