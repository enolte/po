#include <iostream>
#include <cassert>
#include "../../macros.h"

#include "../timed_construct.h"

namespace po_test
{
  void test_vandermonde_rank1_degree1()
  {
    // Knot points, stored in rows here
    static constexpr double p[3][2]
    {
      {0},
      {1},
    };

    // Select knot points by column
    static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };

    auto v = po_test::vandermonde::timed_construct(f, 1, 1);

    PO_ASSERT(v.nrows == 2, v.nrows);
    PO_ASSERT(v.ncols == 2, v.ncols);
    PO_ASSERT(
      equal(
        v.data,
        {                // row multiindices
          1,     1,      // 0
          0,     1,      // 1
        }),
      v);

    PO_LINE;
  }

}