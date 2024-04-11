#ifndef PO_PSEUDOINVERSE_H
#define PO_PSEUDOINVERSE_H

#include "QR.h"
#include "errors.h"
#include "matrix.h"

namespace po
{
  namespace ls
  {
    matrix product(const matrix& x, const matrix& y);

    // Reserving this as a type name for possible future use.
    struct pseudoinverse
    {
      /*
       * Compute a left pseudoinverse of the tall matrix V.
       *
       * assumes: V is tall (num rows >= num cols)
       * assumes: V has full rank
       */
      static matrix compute(const matrix& V, ls::errors* errors = nullptr)
      {
        const std::size_t Q_ncols = V.nrows, Q_nrows = V.nrows;
        const std::size_t R_ncols = V.ncols, R_nrows = V.nrows;
        const std::size_t W_nrows = V.ncols, W_ncols = V.nrows;

        matrix
          Q(Q_nrows, Q_ncols),
          R(R_nrows, R_ncols),
          W(W_nrows, W_ncols);

        //
        // Find a P such that PV = I :
        //

        // 0. Get Q, R: QV = R
        QR(Q, R, V, V.nrows, V.ncols);

        // 1. Solve for W : WR = I
        rt_left_pseudoinverse(W, R);

        // So I = WR = W(QV) = (WQ)V = PV. Since V has full rank,
        // there is such a P. If nrows(V) > nrows(P), P is not unique.
        // The P chosen is the "offset" matrix in an affine space of solutions
        // defined as P = [P1 | T1], where P1 is square, and T1 is arbitrary.
        // Here, we choose T1 := 0.

        // 2. Compute P := WQ.
        const matrix P = product(W, Q);

        // TODO Enable / disable
  #if 0
        using po_test::operator<<;

        PO_TRACE(" ** R =\n" << R);
        PO_TRACE(" ** W =\n" << W);
        PO_TRACE(" ** Q =\n" << Q);
        PO_TRACE(" ** P =\n" << P);
  #endif

        if(errors)
        {
          compute_errors(*errors, Q, R, W, P, V);
        }

        return P;
      }

    private:

      /*
       * Basic BLAS level 2 DGEMM implementation, with a slightly different interface.
       *
       * assumes: x and y have compatible shapes
       */
      static matrix product(const matrix& x, const matrix& y)
      {
        matrix xy(x.nrows, y.ncols);

        for(std::size_t r = 0; r < xy.nrows; ++r)
          for(std::size_t c = 0; c < xy.ncols; ++c)
          {
            double acc = 0.;
            for(std::size_t i = 0; i < x.ncols; ++i)
              // acc += x.data[i + r * x.ncols] * y.data[c + i * y.ncols];
              acc += x[r][i] * y[i][c];
            // xy.data[c + r * xy.ncols] = acc;
            xy[r][c] = acc;
          }

        return xy;
      }

      using vector = std::valarray<double>;

      /*
       * Solve a tall right-triangular row system y = xR for row vector x.
       * The components of y are acquired through a functor interface.
       *
       * assumes: R is tall and has full rank
       */
      static vector rt_left_solve(const point_functor auto& y, const matrix& R)
      {
        vector x(R.nrows);

        double acc = 0.;
        for(std::size_t c = 0; c < R.ncols; ++c)
        {
          acc = y(c);
          for(std::size_t r = 0; r < c; ++r)
          {
            acc -= x[r] * R[r][c];
          }
          x[c] = acc / R[c][c];
        }

        return x;
      }

    public:

      /*
       * Compute a left pseudo-inverse W of the right-triangular matrix R, such that
       * WR = id.
       *
       * assumes: R is tall and has full rank
       */
      static void rt_left_pseudoinverse(matrix& W, const matrix& R)
      {
        // Solve the column system y = xR for each y = Euclidean row basis vector, in standard order
        for(std::size_t c = 0; c < R.ncols; ++c)
        {
          const auto x = rt_left_solve([c](std::size_t c0) { return c0 == c; }, R);
          for(std::size_t r = 0; r < R.nrows; ++r)
          {
            W[c][r] = x[r];
          }

        }
      }

    };
  }

}

#endif

