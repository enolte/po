#ifndef PO_LS_QR_H
#define PO_LS_QR_H

#include <cmath>
#include "concepts.h"
#include "matrix.h"

namespace po
{
  namespace ls
  {
    template<typename F>
      requires (po::matrix<F> || po::matrix_functor<F>)
    constexpr void QR(matrix& Q, matrix& R, F&& f, std::size_t nr, std::size_t nc)
    {
      // Q <-- id
      Q.data = 0;
      Q.data[std::slice(0, nr, nr+1)] = 1;

      const std::size_t nq = nr;

      // R <-- f
      if constexpr(po::matrix<F>)
      {
        R = f;
      }
      else
      {
        for(std::size_t r = 0; r < nr; ++r)
          for(std::size_t c = 0; c < nc; ++c)
            R[r, c] = f(r, c);
      }

      for(std::size_t c = 0; c < nc; ++c)
      {
        const double mcc = R[c, c];
        for(std::size_t r = c+1; r < nr; ++r)
        {
          const double mrc = R[r, c];

          if(mrc == 0. || mrc == -0.)
          {
            continue;
          }

          const double h = std::sqrt(mcc*mcc + mrc*mrc);
          const double cos = mcc / h;
          const double sin =-mrc / h;

          if(sin != sin)
          {
            continue;
          }

          // R <-- <current rotation> * R
          for(std::size_t k = 0; k < nc; ++k)
          {
            const double R_ck = cos * R[c, k]  -  sin * R[r, k];
            const double R_rk = sin * R[c, k]  +  cos * R[r, k];
            R[r, k] = R_rk;
            R[c, k] = R_ck;
          }

          // Q <-- <current rotation> * Q
          for(std::size_t k = 0; k < nq; ++k)
          {
            const double Q_ck = cos * Q[c, k]  -  sin * Q[r, k];
            const double Q_rk = sin * Q[c, k]  +  cos * Q[r, k];
            Q[r, k] = Q_rk;
            Q[c, k] = Q_ck;
          }

        }
      }
    }
  }
}


#endif

