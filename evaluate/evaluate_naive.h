#ifndef PO_EVALUATE_NAIVE_H
#define PO_EVALUATE_NAIVE_H

#include "../scalar.h"

namespace po
{
 /*
  * term-wise sparse naive evaluation
  *
  * Evaluate this polynomial. Intermediate computation results are stored as `double`.
  * The return value is the static cast of the result to `scalar_type`.
  */
  template<typename P, typename ...T>
  scalar_type evaluate_naive(const P& p, T... x)
  {
    double acc = 0.;
    for(const auto& t : p.terms)
      acc += t(x...);

    return scalar_type{acc};
  }


}


#endif


