#ifndef PO_EVALUATE_H
#define PO_EVALUATE_H

// If not defined at command line or elsewhere previously, then set a default here.
#ifndef PO_EVALUATION_IMPL
// #define PO_EVALUATION_IMPL evaluate_naive
#define PO_EVALUATION_IMPL evaluate_gH
#endif

#include "evaluate_naive.h"
#include "evaluate_gH.h"

namespace po
{
  template<is_polynomial P, is_scalar ...X>
  constexpr static double evaluate(const P& p, X&&... x)
  {
    return PO_EVALUATION_IMPL(p, x...);
  }

  template<is_polynomial P, is_scalar ...X>
  constexpr static double evaluate(nargs n, const P& p, X&&... x)
  {
    return PO_EVALUATION_IMPL(n, p, x...);
  }


}

#endif

