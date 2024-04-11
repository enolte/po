#include <iostream>
#include <iomanip>
#include <cassert>
#include <functional>

#include "../../induction/ls/QR.h"
#include "../../induction/ls/matrix.h"
#include "../../induction/ls/concepts.h"
#include "../../induction/ls/errors.h"

#include "matrix_ostream.h"
#include "../macros.h"

namespace po_test
{
  using test_functor = std::function<double(std::size_t, std::size_t)>;

  static const test_functor test_functors[]
  {
    [](std::size_t r, std::size_t c) { return 3.; },
    [](std::size_t r, std::size_t c) { return r + c; },
    [](std::size_t r, std::size_t c) { return r + c*c;},
    [](std::size_t r, std::size_t c) { return r*r + c; },
    [](std::size_t r, std::size_t c) { return r*r + c*c; },
    [](std::size_t r, std::size_t c) { return 1./(1 + (r+c)); },
    [](std::size_t r, std::size_t c) { return 1./(1 + (r+c)*r); },
    [](std::size_t r, std::size_t c) { return (r + c) /(1. + r + c); },
  };

  void test_tall_QR(po::matrix_functor auto&& m, std::size_t nrows, std::size_t ncols, int = -1);

  template<std::size_t nr, std::size_t nc>
  void test_tall_QR()
  {
    static_assert(nc <= nr);

    if constexpr(nr == 3 && nc == 2)
    {
      test_tall_QR
      (
        [](std::size_t r, std::size_t c)
        {
          static constexpr double m[3][2]
          {
            {1, 1},
            {0, 1.2},
            {0, 1},
          };

          return m[r][c];
        }, nr, nc
      );
    }

    int k = -1;
    for(auto f : test_functors)
    {
      test_tall_QR(f, nr, nc, ++k);
    }
  }


  void test_tall_QR(po::matrix_functor auto&& m, std::size_t nrows, std::size_t ncols, int k)
  {
    po::ls::matrix Q(nrows, nrows);
    po::ls::matrix R(nrows, ncols);
    po::ls::QR(Q, R, m, nrows, ncols);

    const double Q_error =  po::ls::compute_Q_error(Q);
    const double R_error =  po::ls::compute_R_error(R);
    const double QR_error = po::ls::compute_QR_error(Q, R, m);

    // Just a basic sanity check for the test cases above.
    static constexpr double tol = 0x1p-30;
    const bool success = Q_error <= tol && R_error <= tol && QR_error <= tol;

    if(!success)
    {
      PO_TRACE("[" << k << "] " << nrows << " x " << ncols);

      PO_TRACE("tol     = " << tol      << " = " << std::hexfloat << tol      << std::defaultfloat);
      PO_TRACE("R_error = " << R_error  << " = " << std::hexfloat << R_error  << std::defaultfloat);
      PO_TRACE("Q_error = " << Q_error  << " = " << std::hexfloat << Q_error  << std::defaultfloat);
      PO_TRACE("QR_error= " << QR_error << " = " << std::hexfloat << QR_error << std::defaultfloat);
    }

    PO_ASSERT(success, success);

    PO_TRACE(PO_MARKER << " " << __func__ << " [" << nrows << " x " << ncols << "] [" << k << "]");
  }

}


