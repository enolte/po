#include <iostream>
#include <cassert>
#include "../../macros.h"

#include "../timed_construct.h"

namespace po_test
{
  namespace rank2_degree2_dim2_simplex_pseudoinverse
  {
    void test1();
    // void test2();
  }

  void test_pseudoinverse_rank2_degree2_dim2_simplex()
  {
    using namespace rank2_degree2_dim2_simplex_pseudoinverse;

    test1();
    // test2();
  }

  namespace rank2_degree2_dim2_simplex_pseudoinverse
  {
    void test1()
    {
      // Simplex knot points, stored in rows here
      static constexpr double points[3][2]
      {
        {0, 0},
        {1, 1},
        {0, 2},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return points[c][r]; };

      po::ls::errors errors;
      auto p = po_test::pseudoinverse::timed_construct(f, 2, 2, 2, errors);

      PO_ASSERT(p.data.size() == 36, p.data.size());
      PO_ASSERT(p.nrows == 6, p.nrows);
      PO_ASSERT(p.ncols == 6, p.ncols);

      // Just a basic sanity check
      static constexpr double tol = 0x1p-48;
      PO_ASSERT(errors.max() <= tol, errors);

      PO_ASSERT(
        abs_near(
          p.data,
          {
  //        column multiindices
  //        0 0       1 0      0 1      2 0      1 1      0 2          row multiindices
            1.0,     -1.5,    -1.5,     0.5,     1.0,     0.5,      // 2 0 0  -->  0  , 0
            0.0,      4.0,     0.0,    -2.0,    -2.0,     0.0,      // 1 1 0  -->  0.5, 0.5
            0.0,     -1.0,     0.0,     2.0,     0.0,     0.0,      // 0 2 0  -->  1  , 1
            0.0,     -2.0,     2.0,     1.0,     0.0,    -1.0,      // 1 0 1  -->  0  , 1
            0.0,      0.0,    -0.0,    -2.0,     2.0,     0.0,      // 0 1 1  -->  0.5, 1.5
            0.0,      0.5,    -0.5,     0.5,    -1.0,     0.5,      // 0 0 2  -->  0  , 2
          }, 0x1p-50),
          p);

      PO_LINE;
    }

  }

}

