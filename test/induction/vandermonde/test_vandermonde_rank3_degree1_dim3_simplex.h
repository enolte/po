#include <iostream>
#include <cassert>
#include "../../macros.h"

#include "../timed_construct.h"

namespace po_test
{
  namespace rank3_degree1_dim3_simplex_vandermonde
  {
    void test1();
    void test2();
  }

  void test_vandermonde_rank3_degree1_dim3_simplex()
  {
    using namespace rank3_degree1_dim3_simplex_vandermonde;

    test1();
    test2();
  }

  namespace rank3_degree1_dim3_simplex_vandermonde
  {
    void test1()
    {
      // Simplex vertex knot points, stored in rows here
      static constexpr double p[][3]
      {
        {0, 0, 0},
        {1, 1, 1},
        {2, 2, 2},
        {3, 3, 3},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };

      auto v = po_test::vandermonde::timed_construct(f, 3, 1, 3);

      PO_ASSERT(v.nrows == 4, v.nrows);
      PO_ASSERT(v.ncols == 4, v.ncols);
      PO_ASSERT(
        equal(
          v.data,
          {
  //        column multiindices
  //        1 0 0 0     0 1 0 0     0 0 1 0     0 0 0 1         row multiindices
            1,          1,          1,          1,           // 0 0 0
            0,          1,          2,          3,           // 1 0 0
            0,          1,          2,          3,           // 0 1 0
            0,          1,          2,          3,           // 0 0 1
          }),
        v);

      PO_LINE;
    }

    void test2()
    {
      // Simplex vertex knot points, stored in rows here
      static constexpr double p[][3]
      {
        {0, 0, 0},
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return p[c][r]; };

      auto v = po_test::vandermonde::timed_construct(f, 3, 1, 3);

      PO_ASSERT(v.nrows == 4, v.nrows);
      PO_ASSERT(v.ncols == 4, v.ncols);
      PO_ASSERT(
        equal(
          v.data,
          {
  //        column multiindices
  //        1 0 0 0     0 1 0 0     0 0 1 0     0 0 0 1         row multiindices
            1,          1,          1,          1,           // 0 0 0
            0,          1,          0,          0,           // 1 0 0
            0,          0,          1,          0,           // 0 1 0
            0,          0,          0,          1,           // 0 0 1
          }),
        v);

      PO_LINE;
    }
  }
}

