#ifndef PO_LAGRANGE_BASIS_H
#define PO_LAGRANGE_BASIS_H

#include "../polynomial.h"
#include <vector>

#include "ls/concepts.h"
#include "ls/vandermonde.h"
#include "ls/pseudoinverse.h"

namespace po
{
  std::vector<polynomial> lagrange_basis(const matrix auto& v, std::size_t rank, std::size_t degree, ls::errors* errors = nullptr);

  /*
   * Construct a Lagrange basis for points of dimension `rank`.
   * Each polynomial has degree <= the given `degree`.
   *
   * The point functor selects point components, as f( ., c) = the cth point (vector) from the domain.
   *
   * assumes: the point functor accesses at least C(rank + degree, degree) many points
   */
  std::vector<polynomial> lagrange_basis(const matrix_functor auto& f, std::size_t rank, std::size_t degree, ls::errors* errors = nullptr)
  {
    ls::matrix v = ls::vandermonde::construct(f, rank, degree);
    return lagrange_basis(v, rank, degree, errors);
  }

  /*
   * Construct a Lagrange basis for points on a simplex K of dimension `simplex_dim`.
   * K is modeled as embedded in `rank` dimensions.
   * Each polynomial has degree <= the given `degree`.
   *
   * The point functor selects point components, as f( ., c) = the cth point (vector) from the domain.
   *
   * assumes: the point functor accesses at least C(simplex_dim + degree, degree) many points
   */
  std::vector<polynomial> lagrange_basis_for_simplex(const matrix_functor auto& f, std::size_t rank, std::size_t degree, std::size_t simplex_dim, ls::errors* errors = nullptr)
  {
    ls::matrix v = ls::vandermonde::construct_for_simplex(f, rank, degree, simplex_dim);
    return lagrange_basis(v, rank, degree, errors);
  }

  std::vector<polynomial> lagrange_basis(const matrix auto& v, std::size_t rank, std::size_t degree, ls::errors* errors)
  {
    ls::matrix p = ls::pseudoinverse::compute(v, errors);

    // TODO Enable / disable
#if 0
    using po_test::operator<<;

    PO_TRACE(" v =\n" << v);
    PO_TRACE(" p =\n" << p);
#endif

    std::vector<polynomial> basis(p.nrows, po::zero(rank));

    // Copy the constant terms (zeroth column).
    for(auto r{0zu}; r < p.nrows; ++r)
    {
      basis[r] += p[r][0];
    }

    // Copy the non-constant terms (columns), one polynomial (= one row) at a time.
    for(auto r{0zu}; r < p.nrows; ++r)
    {
      polynomial b = po::zero(rank);

      std::size_t c{1};
      for(auto d{1zu}; d <= degree; ++d)
      {
        for(exponents_sequence ii(rank, d); !ii.end; ++ii)
        {
          b += {p[r][c], ii.exponents};
          ++c;
        }
      }

      basis[r] += std::move(b);
    }

    return basis;
  }

}

#endif



