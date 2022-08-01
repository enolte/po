#include "is_polynomial.h"
#include "is_expression.h"

#include "is_scalar.h"

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
      return expr_rank(e.expr1);
    else
    {
      const rank_type r1 = expr_rank(e.expr1);
      if (r1 > 0)
        return r1;
      else
        return expr_rank(e.expr2);
    }
  }

}

