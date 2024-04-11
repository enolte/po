#include <iostream>
#include <cassert>
#include "../../macros.h"
#include "../matrix_ostream.h"
#include "../../../ostream/polynomial_ostream.h"

#include "../../../induction/lagrange_basis.h"

#include "verify_lagrange_basis.h"

namespace po_test
{
  namespace rank2_degree1_lagrange_basis
  {
    static constexpr std::uint64_t rank = 2;
    static constexpr std::uint64_t degree = 1;

    void test1();
    void test2();
    void test3();
  }

  void test_lagrange_basis_rank2_degree1()
  {
    using namespace rank2_degree1_lagrange_basis;

    test1();
    test2();
    test3();
  }

  namespace rank2_degree1_lagrange_basis
  {
    // Knot points, stored in rows for fixed i
    static constexpr double points[][3][2]
    {
      {
        {0, 0},
        {1, 1},
        {2, 3},
      },
      {
        {0, 0},
        {-4, 1},
        {2, 7.2},
      },
      {
        {6.2, -3.05},
        {-4.1, 22.2},
        {3, -3.6},
      }
    };

    void test(const double points[3][2], int = -1);

    void test(int k) { test(points[k], k); }

    void test1() { test(0); }
    void test2() { test(1); }
    void test3() { test(2); }

    void test(const double points[3][2], int k)
    {
      // Select knot points by column
      auto f = [points](std::size_t r, std::size_t c) { return points[c][r]; };

      po::ls::errors errors;
      auto basis = po::lagrange_basis(f, 2, 1, &errors);

      // for(auto i{0zu}; i < basis.size(); ++i)
        // PO_TRACE(" basis[" << i << "] = " << basis[i]);

      PO_ASSERT(basis.size() == 3, basis.size());

      // Just a basic sanity check
      static constexpr double tol = 0x1p-48;
      PO_ASSERT(errors.max() <= tol, errors);

      verify_lagrange_basis(basis, points, tol);

      PO_TRACE(PO_MARKER << " " << __func__ << " [rank " << rank << ", degree " << degree << "] [" << k << "]");
    }


  }

}

