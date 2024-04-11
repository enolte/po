#include <iostream>
#include <cassert>
#include "../../macros.h"

#include "../timed_construct.h"

namespace po_test
{
  namespace rank2_degree3_vandermonde
  {
    void test1();
    void test2();
  }

  void test_vandermonde_rank2_degree3()
  {
    using namespace rank2_degree3_vandermonde;

    test1();
    test2();
  }

  namespace rank2_degree3_vandermonde
  {
    void test1()
    {
      // Knot points, stored in rows here
      static constexpr double p[][2]
      {
        {0, 0},
        {1, 1},
        {2, 2},
        {3, 3},
        {4, 4},
        {5, 5},
        {6, 6},
        {7, 7},
        {8, 8},
        {9, 9},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };

      auto v = po_test::vandermonde::timed_construct(f, 2, 3);

      PO_ASSERT(v.nrows == 10, v.nrows);
      PO_ASSERT(v.ncols == 10, v.ncols);
      PO_ASSERT(
        equal(
          v.data,
          {                                                               // row multiindices
            1.,  1.,  1.,   1.,   1.,    1.,    1.,    1.,    1.,    1.,  // 0 0
            0.,  1.,  2.,   3.,   4.,    5.,    6.,    7.,    8.,    9.,  // 1 0
            0.,  1.,  2.,   3.,   4.,    5.,    6.,    7.,    8.,    9.,  // 0 1
            0.,  1.,  4.,   9.,  16.,   25.,   36.,   49.,   64.,   81.,  // 2 0
            0.,  1.,  4.,   9.,  16.,   25.,   36.,   49.,   64.,   81.,  // 1 1
            0.,  1.,  4.,   9.,  16.,   25.,   36.,   49.,   64.,   81.,  // 0 2
            0.,  1.,  8.,  27.,  64.,  125.,  216.,  343.,  512.,  729.,  // 3 0
            0.,  1.,  8.,  27.,  64.,  125.,  216.,  343.,  512.,  729.,  // 2 1
            0.,  1.,  8.,  27.,  64.,  125.,  216.,  343.,  512.,  729.,  // 1 2
            0.,  1.,  8.,  27.,  64.,  125.,  216.,  343.,  512.,  729.,  // 0 3
          }),
        v);

      PO_LINE;
    }

    void test2()
    {
      // Knot points, stored in rows here
      static constexpr double p[][2]
      {
        { 0, 0},
        { 1, 0},
        { 0, 1},
        { 1, 1},
        { 2, 0},
        { 2, 2},
        {-2, 2},
        {-2,-2},
        { 2,-2},
        { 4, 4},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };

      auto v = po_test::vandermonde::timed_construct(f, 2, 3);

      PO_ASSERT(v.nrows == 10, v.nrows);
      PO_ASSERT(v.ncols == 10, v.ncols);
      PO_ASSERT(
        equal(
          v.data,
          {                                                       // row multiindices
            1.,  1.,  1.,  1.,  1.,  1.,   1.,   1.,   1.,   1.,  // 0 0
            0.,  1.,  0.,  1.,  2.,  2.,  -2.,  -2.,   2.,   4.,  // 1 0
            0.,  0.,  1.,  1.,  0.,  2.,   2.,  -2.,  -2.,   4.,  // 0 1
            0.,  1.,  0.,  1.,  4.,  4.,   4.,   4.,   4.,  16.,  // 2 0
            0.,  0.,  0.,  1.,  0.,  4.,  -4.,   4.,  -4.,  16.,  // 1 1
            0.,  0.,  1.,  1.,  0.,  4.,   4.,   4.,   4.,  16.,  // 0 2
            0.,  1.,  0.,  1.,  8.,  8.,  -8.,  -8.,   8.,  64.,  // 3 0
            0.,  0.,  0.,  1.,  0.,  8.,   8.,  -8.,  -8.,  64.,  // 2 1
            0.,  0.,  0.,  1.,  0.,  8.,  -8.,  -8.,   8.,  64.,  // 1 2
            0.,  0.,  1.,  1.,  0.,  8.,   8.,  -8.,  -8.,  64.,  // 0 3
          }),
        v);

      PO_LINE;
    }


  }
}