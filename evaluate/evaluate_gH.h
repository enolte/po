#ifndef PO_EVALUATE_GENERALIZED_HORNER_H
#define PO_EVALUATE_GENERALIZED_HORNER_H

#include "nargs.h"

#include "../ops/is_polynomial.h"
#include "../ops/is_scalar.h"
#include "../types/exponents.h"
#include "../utils/nan.h"

namespace po
{
  namespace detail
  {
    // (Necessary for translation, but never called.)
    template<typename P>
    constexpr static double evaluate_gH(std::size_t nargs, po::exponents& m, const P& p)
    {
      return p.coefficient(m);
    }

    // Generalized Horner evaluation, dense implementation.
    template<typename P, typename X0, typename ...X>
    constexpr static double evaluate_gH(std::size_t nargs, po::exponents& m, const P& p, X0& x0, X&... x)
    {
/*
// PO_TRACE(" nargs = " << nargs << ", sizeof ...(x) = " << sizeof ...(x));
      const std::size_t cur_n = p.rank() - nargs;

      double acc = 0.;
      for(std::size_t d = p.degree(cur_n); d != ~0zu; --d)
      {
        m[cur_n] = d;
        const double s = evaluate_gH(nargs-1, m, p, x...);
        acc = s + x0*acc;
      }

      return acc;
*/

      const std::size_t cur_n = p.rank() - nargs;

      if(nargs == 1)
      {
        double acc = 0.;
        for(std::size_t d = p.degree(cur_n); d != ~0zu; --d)
        {
          m[cur_n] = d;
          const double coeff = p.coefficient(m);
          acc = coeff + x0*acc;
        }

        return acc;
      }
      else
      {
        double acc = 0.;
        for(std::size_t d = p.degree(cur_n); d != ~0zu; --d)
        {
          m[cur_n] = d;
          const double s = evaluate_gH(nargs-1, m, p, x...);
          acc = s + x0*acc;
        }

        return acc;
      }

    }
  }

  template<is_polynomial P, is_scalar ...X>
  constexpr static double evaluate_gH(nargs n, const P& p, X&&... x)
  {
    if(p.rank() == 0)
      return p.constant();
    else
    {
      po::exponents m(0zu, n); // exponent sequence
      return detail::evaluate_gH(n, m, p, x...);
    }
  }

  template<is_polynomial P, is_scalar ...X>
  constexpr static double evaluate_gH(const P& p, X&&... x)
  {
    if(p.rank() == 0)
      return p.constant();
    else
    {
      po::exponents m(0zu, sizeof ...(X)); // exponent sequence
      return detail::evaluate_gH(sizeof ...(x), m, p, x...);
    }
  }

  template<is_polynomial P>
  constexpr static double evaluate_gH(const P& p)
  {
    if(p.rank() == 0)
      return p.constant();
    else
      // (error condition)
      return nan;
  }
}

#endif

