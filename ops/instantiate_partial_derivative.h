#ifndef PO_INSTANTIATE_PARTIAL_DERIVATIVE_H
#define PO_INSTANTIATE_PARTIAL_DERIVATIVE_H

#include "expr_partial_derivative.h"

namespace po
{
  template<typename E1>
    requires expression<E1> && (!scalar<E1>)
  polynomial& instantiate(polynomial& p, const expr_partial_derivative<E1>& expr, rank_type rank)
  {
    instantiate(p, expr.expr1, rank);

    if(expr.place >= p.rank())
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

  template<scalar E1>
  polynomial& instantiate(polynomial& p, const expr_partial_derivative<E1>& expr, rank_type rank)
  {
    p = polynomial::make_zero(rank);
    p += scalar_type{0};
    return p;
  }

}


#endif


