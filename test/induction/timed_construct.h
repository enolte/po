#pragma once

#include "../../induction/ls/vandermonde.h"
#include "../../induction/ls/pseudoinverse.h"
#include "../../induction/lagrange_basis.h"

#include "../macros.h"
#include <chrono>

namespace po_test
{
  namespace vandermonde
  {
    po::ls::matrix timed_construct(po::matrix_functor auto&& f, std::size_t rank, std::size_t degree)
    {
      using clock = std::chrono::high_resolution_clock;
      using namespace std::chrono_literals;

      const clock::time_point t0 = clock::now();

      auto v = po::ls::vandermonde::construct(f, rank, degree);

      const clock::time_point t1 = clock::now();
      const clock::duration t_construct = t1 - t0;

      if(t_construct > 0ns)
      {
        PO_TRACE(" Vandermonde construct time = " << t_construct.count() << " ns");
      }

      return v;
    }

    po::ls::matrix timed_construct(po::matrix_functor auto&& f, std::size_t rank, std::size_t degree, std::size_t simplex_dim)
    {
      using clock = std::chrono::high_resolution_clock;
      using namespace std::chrono_literals;

      const clock::time_point t0 = clock::now();

      auto v = po::ls::vandermonde::construct_for_simplex(f, rank, degree, simplex_dim);

      const clock::time_point t1 = clock::now();
      const clock::duration t_construct = t1 - t0;

      if(t_construct > 0ns)
      {
        PO_TRACE(" Vandermonde simplex construct time = " << t_construct.count() << " ns");
      }

      return v;
    }
  }

  namespace pseudoinverse
  {
    po::ls::matrix timed_construct(po::matrix_functor auto&& f, std::size_t rank, std::size_t degree, po::ls::errors& errors)
    {
      using clock = std::chrono::high_resolution_clock;
      using namespace std::chrono_literals;

      auto v = po::ls::vandermonde::construct(f, rank, degree);

      const clock::time_point t0 = clock::now();

      auto p = po::ls::pseudoinverse::compute(v, &errors);

      const clock::time_point t1 = clock::now();
      const clock::duration t_solve = t1 - t0;

      if(t_solve > 0ns)
      {
        PO_TRACE(" Pseudoinverse solve time = " << t_solve.count() << " ns");
      }

      return p;
    }

    po::ls::matrix timed_construct(po::matrix_functor auto&& f, std::size_t rank, std::size_t degree, std::size_t simplex_dim, po::ls::errors& errors)
    {
      using clock = std::chrono::high_resolution_clock;
      using namespace std::chrono_literals;

      auto v = po::ls::vandermonde::construct_for_simplex(f, rank, degree, simplex_dim);

      const clock::time_point t0 = clock::now();

      auto p = po::ls::pseudoinverse::compute(v, &errors);

      const clock::time_point t1 = clock::now();
      const clock::duration t_solve = t1 - t0;

      if(t_solve > 0ns)
      {
        PO_TRACE(" Pseudoinverse simplex solve time = " << t_solve.count() << " ns");
      }

      return p;
    }
  }

  namespace lagrange_basis
  {
    std::vector<po::polynomial> timed_construct(po::matrix_functor auto&& f, std::size_t rank, std::size_t degree, po::ls::errors& errors)
    {
      using clock = std::chrono::high_resolution_clock;
      using namespace std::chrono_literals;

      const clock::time_point t0 = clock::now();

      auto basis = po::lagrange_basis(f, rank, degree, errors);

      const clock::time_point t1 = clock::now();
      const clock::duration t_solve = t1 - t0;

      if(t_solve > 0ns)
      {
        PO_TRACE(" Lagrange basis solve time = " << t_solve.count() << " ns");
      }

      return basis;
    }

    std::vector<po::polynomial> timed_construct(po::matrix_functor auto&& f, std::size_t rank, std::size_t degree, std::size_t simplex_dim, po::ls::errors& errors)
    {
      using clock = std::chrono::high_resolution_clock;
      using namespace std::chrono_literals;

      const clock::time_point t0 = clock::now();

      auto basis = po::lagrange_basis_for_simplex(f, rank, degree, simplex_dim, &errors);

      const clock::time_point t1 = clock::now();
      const clock::duration t_solve = t1 - t0;

      if(t_solve > 0ns)
      {
        PO_TRACE(" Lagrange basis simplex solve time = " << t_solve.count() << " ns");
      }

      return basis;
    }

  }

}