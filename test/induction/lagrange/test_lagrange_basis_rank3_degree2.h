#include <iostream>
#include <cassert>
#include "../../macros.h"
#include "../matrix_ostream.h"
#include "../../../ostream/polynomial_ostream.h"

#include "../../../induction/lagrange_basis.h"

#include "verify_lagrange_basis.h"

namespace po_test
{
  namespace rank3_degree2_lagrange_basis
  {
    static constexpr std::uint64_t rank = 3;
    static constexpr std::uint64_t degree = 2;

    void test1();
    void test2();
    void test3();
  }

  void test_lagrange_basis_rank3_degree2()
  {
    using namespace rank3_degree2_lagrange_basis;

    test1();

    // TODO
    // test2();
    // test3();
  }

  namespace rank3_degree2_lagrange_basis
  {
    // Knot points, stored in rows for fixed i
    static constexpr double points[][10][3]
    {
      {
        {0, 0, 0},
        {1, 1, 1},
        {2, 3, 4},
        {3, 5, 8},
        {5, 8, 13},
        {8, -13, 21},
        {13, -21, 34},
        {21, -34, 55},
        {34, -55, 89},
        {55, -89, 144},
      },
      {
        {0, 0, 0},
        {-4, 1, 2},
        {2, 7.2, -0.4},
        {-4.2, 1, 4},
        {-3.2, 0, 3},
        {-4.2,-1, 4},
        {-3.2,-2, 5},
        {-4.2,-3, 4},
        {-3.2,-4, 0.2},
        {-4.2,-5, 100.4},
      },
      {
        {6.2, -3.05, 0},
        {-4.1, 22.2, 1},
        {3, -3.6, 2},
        {6.2, -6.05, 3},
        {-4.1, 19.2, 1},
        {-4.1, 19.2, 4},
        {-4.1, 16.2, 7},
        {-4.1, 13.2, 10},
        {-4.1, 10.2, 13},
        {-4.1, 7.2, 16},
      }
    };

    void test(const double points[][3], int = -1);

    void test(int k) { test(points[k], k); }

    void test1() { test(0); }
    void test2() { test(1); }
    void test3() { test(2); }

    void test(const double points[][3], int k)
    {
      // Select knot points by column
      auto f = [points](std::size_t r, std::size_t c) { return points[c][r]; };

      po::ls::errors errors;
      auto basis = po::lagrange_basis(f, 3, 2, &errors);

      // for(auto i{0zu}; i < basis.size(); ++i)
        // PO_TRACE(" basis[" << i << "] = " << basis[i]);

      PO_ASSERT(basis.size() == 10, basis.size());

      // Just a basic sanity check
      static constexpr double tol = 0x1.cp-27;
      PO_ASSERT(errors.max() <= tol, errors << ", " << std::hexfloat << errors << std::defaultfloat);

      verify_lagrange_basis(basis, points, tol);

      PO_TRACE(PO_MARKER << " " << __func__ << " [rank " << rank << ", degree " << degree << "] [" << k << "]");
    }


  }

}

