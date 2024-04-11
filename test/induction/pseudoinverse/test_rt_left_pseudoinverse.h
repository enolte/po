#include <iostream>
#include <iomanip>
#include <cassert>
#include <functional>

#include "../../../induction/ls/pseudoinverse.h"
#include "../../../induction/ls/matrix.h"
#include "../../../induction/ls/concepts.h"
#include "../../../induction/ls/errors.h"

#include "../matrix_ostream.h"
#include "../../macros.h"

namespace po_test
{
  void test_rt_left_pseudoinverse(po::matrix_functor auto&& m, std::size_t nrows, std::size_t ncols, int = -1);

  using test_functor = std::function<double(std::size_t, std::size_t)>;

  static const test_functor rt_test_functors[]
  {
    [](std::size_t r, std::size_t c) { return 3.; },
    [](std::size_t r, std::size_t c) { return 1. + r + c; },
    [](std::size_t r, std::size_t c) { return 1. + r + c*c;},
    [](std::size_t r, std::size_t c) { return 1. + r*r + c; },
    [](std::size_t r, std::size_t c) { return 1. + r*r + c*c; },
    [](std::size_t r, std::size_t c) { return 1./(1 + (r+c)); },
    [](std::size_t r, std::size_t c) { return 1./(1 + (r+c)*r); },
    [](std::size_t r, std::size_t c) { return 1. + (r + c) /(1. + r + c); },
  };

  test_functor rt(test_functor f, std::size_t r, std::size_t c)
  {
    return [f](std::size_t r, std::size_t c) { return (r <= c) * f(r, c); };
  }

  template<std::size_t nr, std::size_t nc>
  void test_rt_left_pseudoinverse()
  {
    static_assert(nc <= nr);

    if constexpr(nr == 3 && nc == 2)
    {
      test_rt_left_pseudoinverse
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
    }

    int k = -1;
    for(auto f : rt_test_functors)
    {
      test_rt_left_pseudoinverse(rt(f, nr, nc), nr, nc, ++k);
    }

  }


  void test_rt_left_pseudoinverse(po::matrix_functor auto&& m, std::size_t nrows, std::size_t ncols, int k)
  {
    po::ls::matrix R(nrows, ncols);
    for(auto i{0zu}; i < nrows; ++i)
      for(auto j{0zu}; j < ncols; ++j)
        R[i][j] = m(i, j);

    po::ls::matrix W(ncols, nrows);
    po::ls::pseudoinverse::rt_left_pseudoinverse(W, R);

    // PO_TRACE(" ** R =\n" << R);
    // PO_TRACE(" ** W =\n" << W);

    const double W_error =  po::ls::compute_W_error(W);
    const double WR_error = po::ls::compute_WR_error(W, R);

    // Just a basic sanity check for the test cases above.
    static constexpr double tol = 0x1p-40;
    const bool success = W_error <= tol && WR_error <= tol;

    if(!success)
    {
      PO_TRACE("[" << k << "] " << nrows << " x " << ncols);

      PO_TRACE("tol     = " << tol      << " = " << std::hexfloat << tol      << std::defaultfloat);
      PO_TRACE("W_error = " << W_error  << " = " << std::hexfloat << W_error  << std::defaultfloat);
      PO_TRACE("WR_error= " << WR_error << " = " << std::hexfloat << WR_error << std::defaultfloat);
    }

    PO_ASSERT(success, success);

    PO_TRACE(PO_MARKER << " " << __func__ << " [" << nrows << " x " << ncols << "] [" << k << "]");
  }

}


