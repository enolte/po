#ifndef PO_INSTANTIATE_PARTIAL_DERIVATIVE_H
#define PO_INSTANTIATE_PARTIAL_DERIVATIVE_H

#include "expr_partial_derivative.h"

namespace po
{
  template<typename E1, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_partial_derivative<E1> expr, Rank&&)
  {
    instantiate(p, expr.expr1, Rank{});

    if(expr.place > p.rank())
    {
      p.zero();
      p += 0;
      return p;
    }

    for(auto& t : p.terms)
    {
      t.coefficient *= t.exponents[expr.place];
      if(t.exponents[expr.place] > 0)
        t.exponents[expr.place]--;
    }

    return p;
  }
}


#endif


