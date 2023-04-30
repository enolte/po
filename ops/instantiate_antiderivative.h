#ifndef PO_INSTANTIATE_ANTIDERIVATIVE_H
#define PO_INSTANTIATE_ANTIDERIVATIVE_H

#include "../utils/pow.h"
#include "expr_antiderivative.h"

#include "is_expression.h"
#include "change_rank.h"

namespace po
{
  template<expression E1>
  polynomial& instantiate(polynomial& p, const expr_antiderivative<E1> expr, rank_type rank)
  {
    instantiate(p, expr.expr1, expr_rank(expr.expr1));

    if(expr.place < p.rank())
    {
      for(auto& t : p.terms)
      {
        t.coefficient /= t.exponents[expr.place] + 1;
        t.exponents[expr.place] += 1;
      }

      p.update_degrees();

      return p;
    }
    else
    {
      detail::increase_rank(p, expr.place + 1);
      for(auto& t : p.terms)
        t.exponents[expr.place] = 1;

      p.update_degrees();

      return p;
    }

  }

  template<constant E1>
  polynomial& instantiate(polynomial& p, const expr_antiderivative<E1> expr, rank_type rank)
  {
    p = polynomial::make_zero(expr.place + 1);

    if constexpr(is_scalar<E1>)
      p += expr.expr1;
    else
      p += expr.expr1.expr1;

    p.terms[0].exponents[expr.place] = 1;
    p.update_degrees();

    return p;
  }

}


#endif


