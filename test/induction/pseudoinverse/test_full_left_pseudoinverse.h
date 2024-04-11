#include <iostream>
#include <iomanip>
#include <cassert>
#include <algorithm>
#include <functional>
// #include <cmath>

#include "../../../induction/ls/pseudoinverse.h"
#include "../../../induction/ls/matrix.h"
#include "../../../induction/ls/concepts.h"
#include "../../../induction/ls/errors.h"

#include "../matrix_ostream.h"
#include "../../macros.h"

namespace po_test
{
  using test_functor = std::function<double(std::size_t, std::size_t)>;

  static const test_functor pseudoinverse_test_functors[]
  {
    [](std::size_t r, std::size_t c) { return 19.3/((r+1)*(r+1) + (c+1)*(c+1)); },
    [](std::size_t r, std::size_t c) { return 1./(1 + (r+c)); },
    [](std::size_t r, std::size_t c) { return 1./(1 + (r+c)*r); },
    [](std::size_t r, std::size_t c) { return (r + c) /(1. + r + c); },
    [](std::size_t r, std::size_t c) { return r == c; },
    // [](std::size_t r, std::size_t c) { return std::sin(r*r+1) * std::cos(c*c+1); },
  };

  void test_full_left_pseudoinverse(po::matrix_functor auto&& m, std::size_t nrows, std::size_t ncols, int = -1);

  template<std::size_t nr, std::size_t nc>
  void test_full_left_pseudoinverse()
  {
    static_assert(nc <= nr);

    if constexpr(nr == 3 && nc == 2)
    {
      test_full_left_pseudoinverse
      (
        [](std::size_t r, std::size_t c)
        {
          static constexpr double m[3][2]
          {
            {1, 1},
            {0, 1.2},
            {0, 0},
          };

          return m[r][c];
        }, nr, nc
      );

      test_full_left_pseudoinverse
      (
        [](std::size_t r, std::size_t c)
        {
          static constexpr double m[3][2]
          {
            {1, 1},
            {9.2, 1.2},
            {-7.07, 0},
          };

          return m[r][c];
        }, nr, nc
      );
    }

    if constexpr(nr == 6 && nc == 6)
    {
      test_full_left_pseudoinverse
      (
        [](std::size_t r, std::size_t c)
        {
          static constexpr double m[6][6]
          {
//           0  1  0  1  2  2
//           0  0  1  1  0  2
            {1, 1, 1, 1, 1, 1}, // 0 0
            {0, 1, 0, 1, 2, 2}, // 1 0
            {0, 0, 1, 1, 0, 2}, // 0 1
            {0, 1, 0, 1, 4, 4}, // 2 0
            {0, 0, 0, 1, 0, 4}, // 1 1
            {0, 0, 1, 1, 0, 4}, // 0 2
          };

          return m[r][c];
        }, nr, nc
      );
    }

    int k = -1;
    for(auto f : pseudoinverse_test_functors)
    {
      test_full_left_pseudoinverse(f, nr, nc, ++k);
    }


  }

  void test_full_left_pseudoinverse(po::matrix_functor auto&& m, std::size_t nrows, std::size_t ncols, int k)
  {
    po::ls::matrix V(nrows, ncols);
    for(auto i{0zu}; i < nrows; ++i)
      for(auto j{0zu}; j < ncols; ++j)
        V[i][j] = m(i, j);

    po::ls::errors errors;
    po::ls::matrix P = po::ls::pseudoinverse::compute(V, &errors);

    assert(P.nrows == V.ncols);
    assert(P.ncols == V.nrows);

    // Just a basic sanity check for the test cases above.
    static constexpr double tol = 0x1p-15;
    // const bool success = max(errors) <= tol;
    const bool success = errors.max() <= tol;
    // PO_TRACE(" " << format << errors << " = " << std::hexfloat << errors << unformat);
    if(!success)
    {
      PO_TRACE("[" << k << "] " << nrows << " x " << ncols);
      PO_TRACE(" tol = " << tol << " = " << std::hexfloat << tol << std::defaultfloat);
      PO_TRACE(" " << format << errors << " = " << std::hexfloat << errors << unformat);
    }

    PO_ASSERT(success, success);

    PO_TRACE(PO_MARKER << " " << __func__ << " [" << nrows << " x " << ncols << "] [" << k << "]");
  }

}


