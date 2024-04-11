#include <iostream>
#include <cassert>
#include "../../macros.h"

#include "../timed_construct.h"

namespace po_test
{
  namespace rank2_degree1_pseudoinverse
  {
    void test1();
    void test2();
  }

  void test_pseudoinverse_rank2_degree1()
  {
    using namespace rank2_degree1_pseudoinverse;

    test1();
    test2();
  }

  namespace rank2_degree1_pseudoinverse
  {
    void test1()
    {
      // Knot points, stored in rows here
      static constexpr double points[3][2]
      {
        {0, 0},
        {1, 1},
        {2, 3},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return points[c][r]; };

      po::ls::errors errors;
      auto p = po_test::pseudoinverse::timed_construct(f, 2, 1, errors);

      PO_ASSERT(p.data.size() == 9, p.data.size());
      PO_ASSERT(p.nrows == 3, p.nrows);
      PO_ASSERT(p.ncols == 3, p.ncols);

      // Just a basic sanity check
      static constexpr double tol = 0x1p-48;
      PO_ASSERT(errors.max() <= tol, errors);

      PO_ASSERT(
        equal(
          p.data,
          {
            1, -2,  1,
            0,  3, -2,
            0, -1,  1
          }),
          p);

      PO_LINE;
    }

    void test2()
    {
      // Knot points, stored in rows here
      static constexpr double points[3][2]
      {
        {0, 0},
        {1, 1},
        {2, 1},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return points[c][r]; };

      po::ls::errors errors;
      auto p = po_test::pseudoinverse::timed_construct(f, 2, 1, errors);

      PO_ASSERT(p.data.size() == 9, p.data.size());
      PO_ASSERT(p.nrows == 3, p.nrows);
      PO_ASSERT(p.ncols == 3, p.ncols);

      // Just a basic sanity check
      static constexpr double tol = 0x1p-48;
      PO_ASSERT(errors.max() <= tol, errors);

      PO_ASSERT(
        equal(
          p.data,
          {
            1,  0, -1,
            0, -1,  2,
            0,  1, -1
          }),
          p);

      PO_LINE;
    }

  }
}