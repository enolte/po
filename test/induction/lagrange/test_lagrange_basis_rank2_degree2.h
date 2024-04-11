#include <iostream>
#include <cassert>
#include "../../macros.h"
#include "../matrix_ostream.h"
#include "../../../ostream/polynomial_ostream.h"

#include "../../../induction/lagrange_basis.h"

#include "verify_lagrange_basis.h"

namespace po_test
{
  namespace rank2_degree2_lagrange_basis
  {
    static constexpr std::uint64_t rank = 2;
    static constexpr std::uint64_t degree = 2;

    void test1();
    void test2();
    void test3();
  }

  void test_lagrange_basis_rank2_degree2()
  {
    using namespace rank2_degree2_lagrange_basis;

    test1();
    test2();
    test3();
  }

  namespace rank2_degree2_lagrange_basis
  {
    // Knot points, stored in rows for fixed zeroth index
    static constexpr double points[][6][2]
    {
      {
        {0, 0},
        {0, 0.5},
        {1, 1},
        {0.5, 0.5},
        {2, 3},
        {1.5, 2},
      },
      {
        {0, 0},
        {1, 0},
        {0, 1},
        {1, 1},
        {2, 0},
        {2, 2},
      },
      {
        {0, 0},
        {1, 1},
        {0, 2},
        {1, 3},
        {0, 4},
        {-1, -1},
      }
    };

    void test(const double points[6][2], int = -1);

    void test(int k) { test(points[k], k); }

    void test1() { test(0); }
    void test2() { test(1); }
    void test3() { test(2); }

    void test(const double points[6][2], int k)
    {
      // Select knot points by column
      auto f = [points](std::size_t r, std::size_t c) { return points[c][r]; };

      po::ls::errors errors;
      auto basis = po::lagrange_basis(f, 2, 2, &errors);

      // for(auto i{0zu}; i < basis.size(); ++i)
        // PO_TRACE(" basis[" << i << "] = " << basis[i]);

      PO_ASSERT(basis.size() == 6, basis.size());

      // Just a basic sanity check
      static constexpr double tol = 0x1p-46;
      PO_ASSERT(errors.max() <= tol, errors << ", " << std::hexfloat << errors << std::defaultfloat);

      verify_lagrange_basis(basis, points, tol);

      PO_TRACE(PO_MARKER << " " << __func__ << " [rank " << rank << ", degree " << degree << "] [" << k << "]");
    }


  }

}

