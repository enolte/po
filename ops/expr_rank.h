#ifndef PO_EXPR_RANK_H
#define PO_EXPR_RANK_H

#include "is_polynomial.h"
#include "is_expression.h"
#include "is_integral.h"
#include "is_scalar.h"
#include "is_extend.h"

namespace po
{
  // TODO This runs inline, but not constexpr: the value of polynomial::rank() is not a compile-time constant.
  template<expression E>
  constexpr rank_type expr_rank(const E& e)
  {
    if constexpr(is_polynomial<E>)
      return e.rank();
    else if constexpr(is_scalar<E>)
      return rank_type{0};
    else if constexpr(is_unary_expression<E>)
    {
      if constexpr(is_integral<E>)
        if(e.place < expr_rank(e.expr1))
          return expr_rank(e.expr1) - 1;
        else
          return expr_rank(e.expr1);
      else if constexpr(is_extend<E>)
        return e.rank;
      else
        return expr_rank(e.expr1);
    }
    else
    {
      const rank_type r1 = expr_rank(e.expr1);
      if (r1 > 0)
        return r1;
      else
        return expr_rank(e.expr2);
    }
  }

  template<expression E1, expression E2>
  constexpr rank_type ranks_compatible(const E1& e1, const E2& e2)
  {
    const rank_type r1 = expr_rank(e1), r2 = expr_rank(e2);
    return r1 == r2 || r1 == 0 || r2 == 0;
  }


}

#endif

