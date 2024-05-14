#ifndef PO_ERRORS_H
#define PO_ERRORS_H

#include <algorithm>
#include "concepts.h"
#include "../../utils/nan.h"

namespace po
{
  namespace ls
  {
    struct errors
    {
      double Q_error{po::nan};
      double R_error{po::nan};
      double QR_error{po::nan};
      double WR_error{po::nan};
      double W_error{po::nan};
      double PV_error{po::nan};

      double max() const
      {
        const double e[] {Q_error, R_error, QR_error, WR_error, W_error, PV_error};

        if(std::ranges::any_of(e, [](double x) { return x != x; }))
          return po::nan;

        return *std::max_element(std::cbegin(e), std::cend(e));
      }
    };

    template<typename ostream>
    ostream& operator<<(ostream& o, const errors& e)
    {
      return o << "errors: {Q: " << e.Q_error << ", R: " << e.R_error << ", QR: " << e.QR_error << ", WR: " << e.WR_error << ", W: " << e.W_error << ", PV: " << e.PV_error << "}";
    }

    double compute_Q_error(const po::matrix auto& Q);
    double compute_R_error(const po::matrix auto& R);

    template<typename M>
      requires (po::matrix<M> || po::matrix_functor<M>)
    double compute_QR_error(const po::matrix auto& Q, const po::matrix auto& R, const M& V);

    double compute_WR_error(const po::matrix auto& W, const po::matrix auto& R);
    double compute_W_error(const po::matrix auto& W);

    template<typename M>
      requires (po::matrix<M> || po::matrix_functor<M>)
    double compute_PV_error(const po::matrix auto& P, const M& V);


    static void compute_errors(
      errors& errors,
      const po::matrix auto& Q,
      const po::matrix auto& R,
      const po::matrix auto& W,
      const po::matrix auto& P,
      const po::matrix auto& V)
    {
      errors.Q_error = compute_Q_error(Q);
      errors.R_error = compute_R_error(R);
      errors.QR_error = compute_QR_error(Q, R, V);
      errors.WR_error = compute_WR_error(W, R);
      errors.PV_error = compute_PV_error(P, V);
      errors.W_error = compute_W_error(W);
    }

    double compute_W_error(const po::matrix auto& W)
    {
      double max_error = -1.;

      // W is wide. Check only the left square.
      for(std::size_t c = 0; c < W.nrows; ++c)
        for(std::size_t r = c+1; r < W.nrows; ++r)
        {
          const double cur_error = std::fabs(W[r][c]);
          if(!(max_error >= cur_error))
          {
            max_error = cur_error;
          }
        }

      return max_error;
    }

    template<typename M>
      requires (po::matrix<M> || po::matrix_functor<M>)
    double compute_QR_error(const po::matrix auto& Q, const po::matrix auto& R, const M& V)
    {
      // product length
      const std::size_t QR_nrows = R.nrows;

      double QR_error = -1.;
      for(std::size_t r = 0; r < R.nrows; ++r)
        for(std::size_t c = 0; c < R.ncols; ++c)
        {
          double acc = 0.;
          for(std::size_t i = 0; i < QR_nrows; ++i)
            acc += Q[i][r] * R[i][c];

          if constexpr(po::matrix<M>)
            acc -= V[r][c];
          else
            acc -= V(r, c);

          QR_error = std::max(QR_error, std::fabs(acc));
        }

      return QR_error;
    }

    double compute_WR_error(const po::matrix auto& W, const po::matrix auto& R)
    {
      const std::size_t WR_nrows = R.ncols, WR_ncols = R.ncols;

      double WR_error = -1.;
      for(std::size_t r = 0; r < WR_nrows; ++r)
        for(std::size_t c = 0; c < WR_ncols; ++c)
        {
          double acc = 0.;
          for(std::size_t i = 0; i < R.nrows; ++i)
            acc += W[r][i] * R[i][c];
          acc -= r == c;
          WR_error = std::max(WR_error, std::fabs(acc));
        }

      return WR_error;
    }

    template<typename M>
      requires (po::matrix<M> || po::matrix_functor<M>)
    double compute_PV_error(const po::matrix auto& P, const M& V)
    {
      const std::size_t PV_nrows = V.ncols, PV_ncols = V.ncols;

      double PV_error = -1.;
      for(std::size_t r = 0; r < PV_nrows; ++r)
        for(std::size_t c = 0; c < PV_ncols; ++c)
        {
          double acc = 0.;
          for(std::size_t i = 0; i < V.nrows; ++i)
            if constexpr (po::matrix<M>)
              acc += P[r][i] * V[i][c];
            else
              acc += P[r][i] * V(i, c);

          acc -= r == c;
          PV_error = std::max(PV_error, std::fabs(acc));
        }

      return PV_error;
    }

    double compute_Q_error(const po::matrix auto& Q)
    {
      double max_error = -1.;

      for(std::size_t r = 0; r < Q.nrows; ++r)
        for(std::size_t c = 0; c < Q.ncols; ++c)
        {
          double acc = 0.;
          for(std::size_t i = 0; i < Q.ncols; ++i)
            acc += Q[r][i] * Q[c][i];
          acc -= (r == c);

          if(max_error < std::fabs(acc))
            max_error = std::fabs(acc);
        }

      return max_error;
    }

    double compute_R_error(const po::matrix auto& R)
    {
      double max_error = -1.;
      for(std::size_t c = 0; c < R.ncols; ++c)
        for(std::size_t r = c+1; r < R.nrows; ++r)
        {
          const double cur_error = std::fabs(R[r][c]);
          if(max_error < cur_error)
            max_error = cur_error;
        }

      return max_error;
    }

  }
}

#endif

