#include <iostream>
#include <cassert>
#include "../../macros.h"

#include "../timed_construct.h"

namespace po_test
{
  namespace rank2_degree2_pseudoinverse
  {
    void test1();
    void test2();
    void test3();
  }

  void test_pseudoinverse_rank2_degree2()
  {
    using namespace rank2_degree2_pseudoinverse;

    test1();
    test2();
    test3();
  }

  namespace rank2_degree2_pseudoinverse
  {
    void test1()
    {
      // Knot points, stored in rows here
      static constexpr double points[][2]
      {
        {0, 0},
        {1, 0},
        {0, 1},
        {1, 1},
        {2, 0},
        {2, 2},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return points[c][r]; };
      // write(std::cout, f, 2, 6);

      po::ls::errors errors;
      auto p = po_test::pseudoinverse::timed_construct(f, 2, 2, errors);

      PO_ASSERT(p.data.size() == 36, p.data.size());
      PO_ASSERT(p.nrows == 6, p.nrows);
      PO_ASSERT(p.ncols == 6, p.ncols);

      // Just a basic sanity check
      static constexpr double tol = 0x1p-48;
      PO_ASSERT(errors.max() <= tol, errors);

      PO_ASSERT(
        equal(
          p.data,
          {
            1., -1.5,  0. ,  0.5,  1., -1. ,
            0.,  2. , -2. , -1. , -1.,  2. ,
            0.,  0. ,  0. ,  0. , -1.,  1. ,
            0.,  0. ,  2. ,  0. ,  1., -2. ,
            0., -0.5,  0.5,  0.5,  0., -0.5,
            0.,  0. , -0.5,  0. ,  0.,  0.5,
          }),
          p);

      PO_LINE;
    }

    void test2()
    {
      // Knot points, stored in rows here
      static constexpr double points[][2]
      {
        {0, 0},
        {1, 1},
        {0, 2},
        {1, 3},
        {0, 4},
        {-1, -1},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return points[c][r]; };
      // write(std::cout, f, 2, 6);

      po::ls::errors errors;
      auto p = po_test::pseudoinverse::timed_construct(f, 2, 2, errors);

      PO_ASSERT(p.data.size() == 36, p.data.size());
      PO_ASSERT(p.nrows == 6, p.nrows);
      PO_ASSERT(p.ncols == 6, p.ncols);

      // PO_TRACE(" v =\n" << v);
      // PO_TRACE(" p =\n" << p);

      // Just a basic sanity check
      static constexpr double tol = 0x1p-48;
      PO_ASSERT(errors.max() <= tol, errors);

      PO_ASSERT(
        abs_near(
          p.data,
          {
            1., +0.75, -0.75, -1.375, +0.25, +0.125,
            0., +0.50, +0.00, +1.000, -0.50, -0.000,
            0., -1.00, +1.00, +0.250, +0.00, -0.250,
            0., +0.00, +0.00, -0.500, +0.50, +0.000,
            0., +0.25, -0.25, +0.125, -0.25, +0.125,
            0., -0.50, +0.00, +0.500, +0.00, +0.000,
          }, 0x1p-45),
          p);

      PO_LINE;
    }

    void test3()
    {
      // Knot points, stored in rows here
      static constexpr double points[][2]
      {
        {0, 0},
        {1, 1},
        {2, 3},
        {3, 4},
        {4, 5},
        {5, 7},
      };

      // Select knot points by column
      static constexpr auto f = [](std::size_t r, std::size_t c) { return points[c][r]; };
      // write(std::cout, f, 2, 6);

      po::ls::errors errors;
      auto p = po_test::pseudoinverse::timed_construct(f, 2, 2, errors);

      PO_ASSERT(p.data.size() == 36, p.data.size());
      PO_ASSERT(p.nrows == 6, p.nrows);
      PO_ASSERT(p.ncols == 6, p.ncols);

      // PO_TRACE(" v =\n" << v);
      // PO_TRACE(" p =\n" << p);

      // Just a basic sanity check
      static constexpr double tol = 0x1p-40;
      PO_ASSERT(errors.max() <= tol, errors);

      PO_ASSERT(
        abs_near(
          p.data,
          {
            +1., -2.0, +1.0,  -3.0,  +5., -2.0,
            +0., +3.5, -2.5,  +3.5,  -6., +2.5,
            +0., -2.5, +2.0,  +7.5, -11., +4.0,
            +0., +2.0, -1.0, -13.0, +19., -7.0,
            +0., -1.5, +1.0,  +4.5,  -6., +2.0,
            +0., +0.5, -0.5,  +0.5,  -1., +0.5,
          }, 0x1p-41),
          p);

      PO_LINE;
    }


  }
}