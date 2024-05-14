#include <iostream>
#include <cassert>
#include "../../macros.h"
#include "../matrix_ostream.h"
#include "../../../ostream/polynomial_ostream.h"

#include "../../../induction/lagrange_basis.h"

#include "../timed_construct.h"
#include "verify_lagrange_basis.h"

namespace po_test
{
  namespace rank7_degree5_dim4_lagrange_simplex_basis
  {
    static constexpr std::uint64_t rank = 7;
    static constexpr std::uint64_t degree = 5;
    static constexpr std::uint64_t simplex_dim = 4;

    void test1();
    void test2();
    void test3();
  }

  void test_lagrange_basis_rank7_degree5_dim4_simplex()
  {
    using namespace rank7_degree5_dim4_lagrange_simplex_basis;

    test1();
    test2();
    test3();
  }

  namespace rank7_degree5_dim4_lagrange_simplex_basis
  {
    // Simplex vertices, stored in rows for fixed zeroth index
    static constexpr double vertices[][simplex_dim+1][rank]
    {
      {
        {-2,  0,   0,   7, 0, 0, 0},
        { 3,  1,   1, 0, 0, 0, 14},
        { 3,  0, 0, 0, 0,  2,  -7},
        {-7, 0, 0, 0, 7,  -7, -14},
        {0, 0, 0, -7,  8, 9.9, -14},
      },
      {
        {0  , -1.1 ,  0  , -5.5, 0, 0, 0},
        {1  ,  0.78,  1.3, 0, 0, 0,  0.},
        {0  , 14.7 , 0, 0, 0, 2  ,  3},
        {0.1, 0, 0, 0, 22.1 ,  3.5, -10.},
        {0, 0, 0, 2.1, 22.01, 13.5,  31.47}
      },
      {
        { 12.7 ,  -9.4  , 30.4,  4.05, 0, 0, 0},
        {  1.06,  -5.1  ,  1.3, 0, 0, 0, 14.05},
        {  9.11, -61.1  , 0, 0, 0, 70.9,  4.99},
        {-14.5 , 0, 0, 0,  0.147,  2.2, -6.616},
        {0, 0, 0,  5.2 ,   5.6  ,  5.8,  7.2}
      },
    };

    void test(const double vertices[][rank], int = -1);

    void test(int k) { test(vertices[k], k); }

    void test1() { test(0); }
    void test2() { test(1); }
    void test3() { test(2); }

    void test(const double vertices[][rank], int k)
    {
      // Select vertices by column
      auto f = [vertices](std::size_t r, std::size_t c) { return vertices[c][r]; };

      po::ls::errors errors;
      // auto basis = po::lagrange_basis_for_simplex(f, rank, degree, simplex_dim, &errors);
      auto basis = lagrange_basis::timed_construct(f, rank, degree, simplex_dim, errors);

      // for(auto i{0zu}; i < basis.size(); ++i)
        // PO_TRACE(" basis[" << i << "] = " << basis[i]);

      PO_ASSERT(basis.size() == 126, basis.size());

      // Just a basic sanity check
      static constexpr double tol = 0x1p-09;
      PO_ASSERT(errors.max() <= tol, errors << ", " << std::hexfloat << errors << std::defaultfloat);

      verify_lagrange_simplex_basis(basis, vertices, degree, simplex_dim, tol);

      PO_TRACE(PO_MARKER << " " << __func__ << " [rank " << rank << ", degree " << degree << ", simplex dim " << simplex_dim << "] [" << k << "]");
    }


  }

}


