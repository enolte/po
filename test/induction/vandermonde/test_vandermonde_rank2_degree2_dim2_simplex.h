#include <iostream>
#include <cassert>
#include "../../macros.h"

#include "../timed_construct.h"

namespace po_test
{
  namespace rank2_degree2_dim2_simplex_vandermonde
  {
    void test1();
    void test2();
  }

  void test_vandermonde_rank2_degree2_dim2_simplex()
  {
    using namespace rank2_degree2_dim2_simplex_vandermonde;

    test1();
    test2();
  }

  namespace rank2_degree2_dim2_simplex_vandermonde
  {
    void test1()
    {
      // Simplex vertex knot points, stored in rows here
      static constexpr double p[3][2]
      {
        {0, 0},
        {1, 1},
        {2, 2},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };

      auto v = po_test::vandermonde::timed_construct(f, 2, 2, 2);
      // PO_TRACE("v = \n" << v);

      PO_ASSERT(v.nrows == 6, v.nrows);
      PO_ASSERT(v.ncols == 6, v.ncols);
      PO_ASSERT(
        equal(
          v.data,
          {
  //        column multiindices
  //        2 0 0     1 1 0    0 2 0    1 0 1    0 1 1    0 0 2      row multiindices
            1.,       1.,      1.,      1.,      1.,      1.,        // 0 0
            0.,       0.5,     1.,      1.,      1.5,     2.,        // 1 0
            0.,       0.5,     1.,      1.,      1.5,     2.,        // 0 1
            0.,       0.25,    1.,      1.,      2.25,    4.,        // 2 0
            0.,       0.25,    1.,      1.,      2.25,    4.,        // 1 1
            0.,       0.25,    1.,      1.,      2.25,    4.         // 0 2
          }),
        v);

      PO_LINE;
    }

    // Invertible V
    void test2()
    {
      // Simplex vertex knot points, stored in rows here
      static constexpr double p[3][2]
      {
        {0, 0},
        {1, 1},
        {0, 2},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };

      auto v = po_test::vandermonde::timed_construct(f, 2, 2, 2);
      // PO_TRACE("v = \n" << v);

      PO_ASSERT(v.nrows == 6, v.nrows);
      PO_ASSERT(v.ncols == 6, v.ncols);
      PO_ASSERT(
        equal(
          v.data,
          {
  //        column multiindices
  //        2 0 0     1 1 0    0 2 0    1 0 1    0 1 1    0 0 2      row multiindices
            1.,       1.,      1.,      1.,      1.,      1.,        // 0 0
            0.,       0.5,     1.,      0.,      0.5,     0.,        // 1 0
            0.,       0.5,     1.,      1.,      1.5,     2.,        // 0 1
            0.,       0.25,    1.,      0.,      0.25,    0.,        // 2 0
            0.,       0.25,    1.,      0.,      0.75,    0.,        // 1 1
            0.,       0.25,    1.,      1.,      2.25,    4.         // 0 2
          }),
        v);

      PO_LINE;
    }

  }
}