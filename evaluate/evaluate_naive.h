#ifndef PO_EVALUATE_NAIVE_H
#define PO_EVALUATE_NAIVE_H

#include "nargs.h"

#include "../ops/is_polynomial.h"
#include "../ops/is_scalar.h"
#include "../types/scalar.h"

namespace po
{
 /*
  * term-wise sparse naive evaluation
  *
  * Evaluate this polynomial. Intermediate computation results are stored as `double`.
  * The return value is the static cast of the result to `scalar_type`.
  */
  template<is_polynomial P, is_scalar ...X>
  scalar_type evaluate_naive(const P& p, X... x)
  {
    double acc = 0.;
    for(const auto& t : p.terms)
      acc += t(x...);

    return scalar_type{acc};
  }

  template<is_polynomial P, is_scalar ...X>
  scalar_type evaluate_naive(nargs n, const P& p, X... x)
  {
    double acc = 0.;
    for(const auto& t : p.terms)
      acc += t(n, x...);

    return scalar_type{acc};
  }

}


#endif


