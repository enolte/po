#ifndef PO_VANDERMONDE_H
#define PO_VANDERMONDE_H

#include "../../utils/pow.h"
#include "../../utils/binomial.h"
#include "exponents_sequence.h"
#include "matrix.h"
#include "concepts.h"

namespace po
{
  namespace ls
  {
    using point = std::valarray<double>;

    // Reserving this as a type name for possible future use.
    struct vandermonde
    {
      /*
       * Construct a Vandermonde matrix in n=`dim` many variables with the given `degree`.
       *
       * assumes: Each column of f is an n-dimensional point. n = `dim`.
       */
      static ls::matrix construct(const matrix_functor auto& f, std::size_t dim, std::size_t degree)
      {
        const std::uint64_t nrows{utils::C(dim + degree, degree)};
        const std::uint64_t ncols{utils::C(dim + degree, degree)};

        ls::matrix v(nrows, ncols);

        point knot(dim);

        for(auto c{0zu}; c < ncols; ++c)
        {
          for(auto r{0zu}; r < dim; ++r)
            knot[r] = f(r, c);

          assign_column(v.data, c, knot, degree, dim, ncols);
        }

        return v;
      }

      /*
       * Construct a Vandermonde matrix in n=`dim` many variables with the given `degree`.
       *
       * Each knot point is a convex combination of the vertices of k-dimensional simplex. k = `simplex_dim`.
       *
       * assumes: Each column of f is an n-dimensional vertex of a k-dimensional simplex.
       */
      static ls::matrix construct_for_simplex(const matrix_functor auto& f, std::size_t dim, std::size_t degree, std::size_t simplex_dim)
      {
        const std::uint64_t nrows{utils::C(dim + degree, degree)};
        const std::uint64_t ncols{utils::C(simplex_dim + degree, degree)};

        ls::matrix v(nrows, ncols);

        point knot(dim);

        std::size_t c{0};
        for(exponents_sequence col(simplex_dim+1, degree); !col.end; ++col)
        {
          const auto knot = simplex_knot_point(f, col, dim);

          assign_column(v.data, c, knot, degree, dim, ncols);

          ++c;
        }

        return v;
      }

    private:

      static double evaluate(const point& p, const exponents_sequence& α)
      {
        double acc = 1.;
        for(std::size_t j = 0; j < α.npoints(); ++j)
          acc *= utils::pow(p[j], α[j]);

        return acc;
      }

      /*
       * Define the components of exactly one column from the multiindex sequence applied
       * to the given knot point.
       */
      static void assign_column(
        std::valarray<double>& data,
        std::size_t c,
        const point& knot,
        std::size_t d,
        std::size_t n,
        std::size_t ncols)
      {
        data[c] = 1.;

        std::size_t r{1};
        for(std::size_t length{1}; length <= d; ++length)
        {
          exponents_sequence row(n, length);
          while(!row.end)
          {
            data[c + r * ncols] = evaluate(knot, row);
            ++row;
            ++r;
          }
        }
      }

    public:

      /*
       * Get a linear-convex combination of the vertex points defined by f
       */
      static const point simplex_knot_point(
        const matrix_functor auto& f,
        const exponents_sequence& alpha,
        std::size_t n)
      {
        const std::size_t length= alpha.length();
        const std::size_t ncols = alpha.npoints();

        // PO_TRACE("  alpha.npoints() = " << alpha.npoints());

        point wsum(0., n);
        for(std::size_t r = 0; r < n; ++r)
          for(std::size_t c = 0; c < ncols; ++c)
          {
            // PO_TRACE("  f(" << r << ", " << c <<") = " << f(r, c));
            wsum[r] += f(r, c) * alpha[c];
          }

        return wsum / length;
      }

#if 0
      static std::valarray<double> _construct_for_simplex(
        point_functor& f,
        std::size_t n,
        std::size_t k,
        std::size_t d,
        std::size_t nrows,
        std::size_t ncols)
      {
        std::valarray<double> data(nrows*ncols);

        exponents_sequence col(k+1, d);
        // PO_TRACE(col.count());

        std::size_t c{0};
        while(!col.end)
        {
          // PO_TRACE(" ** col = " << col << ", c = " << c);

          const auto knot = _knot(f, col, n);

          _assign_column(data, c, knot, d, n, ncols);

          ++col;
          ++c;
        }

        return data;
      }


      vandermonde::vandermonde(
        std::size_t _n,
        std::size_t _k,
        std::size_t _d,
        point_functor _point_functor)
      : nrows{utils::C(_n + _d, _d)},
        ncols{utils::C(_k + _d, _d)},
        n{_n},
        k{_k},
        d{_d},
        data{
          _construct_for_simplex(
            _point_functor,
            n,
            k,
            d,
            nrows,
            ncols)}
      {}
#endif


    };
  }
}

#endif

