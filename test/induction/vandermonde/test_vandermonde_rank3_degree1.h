#include <iostream>
#include <cassert>
#include "../../macros.h"

#include "../timed_construct.h"

namespace po_test
{
  void test_vandermonde_rank3_degree1()
  {
    // Knot points, stored in rows here
    static constexpr double p[][3]
    {
      {0, 0, 0},
      {1, 1, 1},
      {2, 2, 2},
      {3, 3, 3},
    };

    // Select knot points by column
    static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };
    // write(std::cout, f, 3, 4);

    auto v = po_test::vandermonde::timed_construct(f, 3, 1);

    PO_ASSERT(v.nrows == 4, v.nrows);
    PO_ASSERT(v.ncols == 4, v.ncols);
    PO_ASSERT(
      equal(
        v.data,
        {                              // row multiindices
          1,     1,     1,     1,      // 0 0 0
          0,     1,     2,     3,      // 1 0 0
          0,     1,     2,     3,      // 0 1 0
          0,     1,     2,     3,      // 0 0 1
        }),
      v);

    PO_LINE;
  }

}

