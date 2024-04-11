#include <iostream>
#include <cassert>
#include "../../macros.h"

#include "../timed_construct.h"

namespace po_test
{
  namespace rank2_degree2_vandermonde
  {
    void test1();
    void test2();
    void test3();
  }

  void test_vandermonde_rank2_degree2()
  {
    using namespace rank2_degree2_vandermonde;

    test1();
    test2();
    test3();
  }

  namespace rank2_degree2_vandermonde
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
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };
      // write(std::cout, f, 2, 6);

      auto v = po_test::vandermonde::timed_construct(f, 2, 2);

      PO_ASSERT(v.nrows == 6, v.nrows);
      PO_ASSERT(v.ncols == 6, v.ncols);
      PO_ASSERT(
        equal(
          v.data,
          {                                         // row multiindices
            1.,    1.,   1.,   1.,   1.,   1.,      // 0, 0
            0.,    1.,   2.,   3.,   4.,   5.,      // 1, 0
            0.,    1.,   2.,   3.,   4.,   5.,      // 0, 1
            0.,    1.,   4.,   9.,   16.,  25.,     // 2, 0
            0.,    1.,   4.,   9.,   16.,  25.,     // 1, 1
            0.,    1.,   4.,   9.,   16.,  25.,     // 0, 2
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
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };
      // write(std::cout, f, 2, 6);

      auto v = po_test::vandermonde::timed_construct(f, 2, 2);

      PO_ASSERT(v.nrows == 6, v.nrows);
      PO_ASSERT(v.ncols == 6, v.ncols);
      PO_ASSERT(
        equal(
          v.data,
          {                                         // row multiindices
            1.,    1.,   1.,   1.,   1.,   1.,      // 0, 0
            0.,    1.,   0.,   1.,   2.,   2.,      // 1, 0
            0.,    0.,   1.,   1.,   0.,   2.,      // 0, 1
            0.,    1.,   0.,   1.,   4.,   4.,      // 2, 0
            0.,    0.,   0.,   1.,   0.,   4.,      // 1, 1
            0.,    0.,   1.,   1.,   0.,   4.,      // 0, 2
          }),
        v);

      PO_LINE;
    }

    void test3()
    {
      // Knot points, stored in rows here
      static constexpr double p[][2]
      {
        { 1, 0},
        {-1, 0},
        { 0, 1},
        { 0,-1},
        { 1, 1},
        {-1, 1},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };
      // write(std::cout, f, 2, 6);

      auto v = po_test::vandermonde::timed_construct(f, 2, 2);

      PO_ASSERT(v.nrows == 6, v.nrows);
      PO_ASSERT(v.ncols == 6, v.ncols);
      PO_ASSERT(
        equal(
          v.data,
          {                                         // row multiindices
            1.,    1.,   1.,   1.,   1.,   1.,      // 0, 0
            1.,   -1.,   0.,   0.,   1.,  -1.,      // 1, 0
            0.,    0.,   1.,  -1.,   1.,   1.,      // 0, 1
            1.,    1.,   0.,   0.,   1.,   1.,      // 2, 0
            0.,    0.,   0.,   0.,   1.,  -1.,      // 1, 1
            0.,    0.,   1.,   1.,   1.,   1.,      // 0, 2
          }),
        v);

      PO_LINE;
    }

  }
}