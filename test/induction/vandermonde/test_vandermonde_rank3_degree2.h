#include <iostream>
#include <cassert>
#include "../../macros.h"

#include "../timed_construct.h"

namespace po_test
{
  void test_vandermonde_rank3_degree2()
  {
    // Knot points, stored in rows here
    static constexpr double p[][3]
    {
      {0, 0, 0},
      {1, 1, 1},
      {2, 2, 2},
      {3, 3, 3},
      {4, 4, 4},
      {5, 5, 5},
      {6, 6, 6},
      {7, 7, 7},
      {8, 8, 8},
      {9, 9, 9},
    };
    // Select knot points by column
    static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };
    // write(std::cout, f, 3, 10);

    auto v = po_test::vandermonde::timed_construct(f, 3, 2);

    PO_ASSERT(v.nrows == 10, v.nrows);
    PO_ASSERT(v.ncols == 10, v.ncols);
    PO_ASSERT(
      equal(
        v.data,
        {                                                                        //   row multiindices
          1.,    1.,    1.,    1.,    1.,    1.,    1.,    1.,    1.,    1.,     // 0 0 0
          0.,    1.,    2.,    3.,    4.,    5.,    6.,    7.,    8.,    9.,     // 1 0 0
          0.,    1.,    2.,    3.,    4.,    5.,    6.,    7.,    8.,    9.,     // 0 1 0
          0.,    1.,    2.,    3.,    4.,    5.,    6.,    7.,    8.,    9.,     // 0 0 1
          0.,    1.,    4.,    9.,    16.,   25.,   36.,   49.,   64.,   81.,    // 2 0 0
          0.,    1.,    4.,    9.,    16.,   25.,   36.,   49.,   64.,   81.,    // 1 1 0
          0.,    1.,    4.,    9.,    16.,   25.,   36.,   49.,   64.,   81.,    // 0 2 0
          0.,    1.,    4.,    9.,    16.,   25.,   36.,   49.,   64.,   81.,    // 1 0 1
          0.,    1.,    4.,    9.,    16.,   25.,   36.,   49.,   64.,   81.,    // 0 1 1
          0.,    1.,    4.,    9.,    16.,   25.,   36.,   49.,   64.,   81.,    // 0 0 2
        }),
      v);

    PO_LINE;
  }

}

