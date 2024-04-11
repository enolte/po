#include <iostream>
#include <cassert>
#include "../../macros.h"
#include "../matrix_ostream.h"
#include "../../../ostream/polynomial_ostream.h"

#include "../../../induction/lagrange_basis.h"

#include "verify_lagrange_basis.h"

namespace po_test
{
  namespace rank2_degree1_dim2_lagrange_simplex_basis
  {
    static constexpr std::uint64_t rank = 2;
    static constexpr std::uint64_t degree = 1;
    static constexpr std::uint64_t simplex_dim = 2;

    void test1();
    void test2();
    void test3();
  }

  void test_lagrange_basis_rank2_degree1_dim2_simplex()
  {
    using namespace rank2_degree1_dim2_lagrange_simplex_basis;

    test1();
    test2();
    test3();
  }

  namespace rank2_degree1_dim2_lagrange_simplex_basis
  {
    // Simplex vertices, stored in rows in rows for fixed zeroth index
    static constexpr double vertices[][3][2]
    {
      {
        {0, 0},
        {1, 1},
        {0, 2},
      },
      {
        {0, 0},
        {1, 1.3},
        {0, 2},
      },
      {
        {12.7, 30.4},
        {1.06, 1.3},
        {-14.5, 2.2},
      },
    };

    void test(const double vertices[][2], int = -1);

    void test(int k) { test(vertices[k], k); }

    void test1() { test(0); }
    void test2() { test(1); }
    void test3() { test(2); }

    void test(const double vertices[][2], int k)
    {
      // Select vertices by column
      auto f = [vertices](std::size_t r, std::size_t c) { return vertices[c][r]; };

      po::ls::errors errors;
      auto basis = po::lagrange_basis_for_simplex(f, rank, degree, simplex_dim, &errors);

      // for(auto i{0zu}; i < basis.size(); ++i)
        // PO_TRACE(" basis[" << i << "] = " << basis[i]);

      PO_ASSERT(basis.size() == 3, basis.size());

      // Just a basic sanity check
      static constexpr double tol = 0x1p-43;
      PO_ASSERT(errors.max() <= tol, errors << ", " << std::hexfloat << errors << std::defaultfloat);

      verify_lagrange_simplex_basis(basis, vertices, degree, simplex_dim, tol);

      PO_TRACE(PO_MARKER << " " << __func__ << " [rank " << rank << ", degree " << degree << ", simplex dim " << simplex_dim << "] [" << k << "]");
    }


  }

}

