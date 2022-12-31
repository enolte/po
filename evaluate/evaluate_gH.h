#ifndef PO_EVALUATE_GENERALIZED_HORNER_H
#define PO_EVALUATE_GENERALIZED_HORNER_H

#include "../exponents.h"
#include "../nan.h"

namespace po
{
  namespace detail
  {
    // Generalized Horner evaluation, dense implementation.
    template<typename P, typename X0, typename ...X>
    constexpr static double evaluate_gH(po::exponents& m, const P& p, X0& x0, X&... x)
    {
      constexpr std::size_t nargs = 1 + sizeof ...(X);
      const std::size_t cur_n = p.rank() - nargs;

      if constexpr(sizeof ...(X) == 0)
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
          const double s = evaluate_gH(m, p, x...);
          acc = s + x0*acc;
        }

        return acc;
      }
    }
  }

  template<typename P, typename ...X>
  constexpr static double evaluate_gH(const P& p, X&&... x)
  {
    if(p.rank() == 0)
      return p.constant();
    else
    {
      po::exponents m(0zu, sizeof ...(X)); // exponent sequence
      return detail::evaluate_gH(m, p, x...);
    }
  }

  template<typename P>
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

