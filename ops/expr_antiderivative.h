#ifndef PO_EXPR_ANTIDERIVATIVE_H
#define PO_EXPR_ANTIDERIVATIVE_H

#include "is_expression.h"
#include "../types/rank.h"


namespace po
{
  template<expression>
  struct expr_antiderivative;
}

// Specializations of expr_antiderivative
#include "expr_antiderivative_constant.h"
#include "expr_antiderivative_polynomial.h"
#include "expr_antiderivative_binary_plus.h"
#include "expr_antiderivative_binary_minus.h"
#include "expr_antiderivative_binary_mult.h"
#include "expr_antiderivative_unary_minus.h"
#include "expr_antiderivative_unary_plus.h"
#include "expr_antiderivative_partial_derivative.h"
#include "expr_antiderivative_integral.h"
#include "expr_antiderivative2.h"

namespace po
{
  template<expression E1, typename ...Places>
  constexpr auto antiderivative(E1&& expr, rank_type place, Places&&... places)
  {
    if constexpr(sizeof ...(places) > 0)
    {
      return antiderivative(antiderivative(std::forward<E1>(expr), place), places...);
    }
    else
    {
      if constexpr(is_constant<E1>)
        return expr_antiderivative<expr_constant>{expr, place};
      else
        return expr_antiderivative<E1>{std::forward<E1>(expr), place};
    }
  }
}


#endif


