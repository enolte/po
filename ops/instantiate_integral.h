#ifndef PO_INSTANTIATE_INTEGRAL_H
#define PO_INSTANTIATE_INTEGRAL_H

#include "../utils/pow.h"
#include "expr_integral.h"

#include "is_expression.h"
#include "change_rank.h"

namespace po
{
  template<expression E1>
  polynomial& instantiate(polynomial& p, const expr_integral<E1> expr, rank_type rank)
  {
    instantiate(p, expr.expr1, expr_rank(expr.expr1));

    if(expr.place < p.rank())
    {
      for(auto& t : p.terms)
      {
        t.coefficient /= t.exponents[expr.place] + 1;
        t.coefficient *= pow(expr.b, t.exponents[expr.place] + 1) - pow(expr.a, t.exponents[expr.place] + 1);
      }

      detail::decrease_rank(p, expr.place);

      p.update_degrees();

      return p;
    }
    else
    {
      p *= expr.b - expr.a;
      return p;
    }

  }

  template<constant E1>
  polynomial& instantiate(polynomial& p, const expr_integral<E1> expr, rank_type rank)
  {
    p = polynomial::make_zero(rank);

    if constexpr(is_scalar<E1>)
      p += expr.expr1 * (expr.b - expr.a);
    else
      p += expr.expr1.expr1 * (expr.b - expr.a);

    return p;
  }

}


#endif


