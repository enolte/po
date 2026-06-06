#ifndef PO_EXPR_EXTEND_H
#define PO_EXPR_EXTEND_H

#include <array>

#include "is_expression.h"
#include "../types/rank.h"

namespace po
{
  template<expression, typename = void>
  struct expr_extend;
}

// Specializations of expr_extend
#include "expr_extend_constant.h"
#include "expr_extend_polynomial.h"
// TODO
// #include "expr_extend_binary_plus.h"
// #include "expr_extend_binary_minus.h"
// #include "expr_extend_binary_mult.h"
// #include "expr_extend_unary_minus.h"
// #include "expr_extend_unary_plus.h"
// #include "expr_extend_partial_derivative.h"
// #include "expr_extend_antiderivative.h"
// #include "expr_extend_integral.h"
// #include "expr_extend2.h"

#include "is_constant.h"

namespace po
{
  /*
   * Extend the signature of the given expression to the given rank,
   * by using the values of the numerical arguments at the given places.
   *
   * E.g., given p(x, y), then x = po::extend(p, 4, 2, 3) defines an `x`
   * such that x(a, b, x, y) == p(x, y) for all a, b, x, y.
   *
   * By intent, x is independent of a and b. It is an expression which is
   * signature-compatible with any other rank 4 expression, and which carries
   * the values of rank-2 p(x, y) upon evaluation.
   *
   * The param pack Places defines the locations of the args of p in th
   * extended signature.
   *
   * assumes: Values in places... are distinct, and all < rank.
   */
  constexpr auto extend(expression auto&& expr, rank_type rank, std::integral auto... places)
  {
    // Handle FP numeric expr type and expr_constant type as special cases.
    if constexpr(is_constant<decltype(expr)> && !is_scalar<decltype(expr)>)
    {
      return expr_extend<po::scalar_type>{(po::scalar_type)expr.expr1, rank};
    }
    else if constexpr(is_scalar<decltype(expr)>)
    {
      return expr_extend<po::scalar_type>{(po::scalar_type)expr, rank};
    }
    else
    {
      return expr_extend<decltype(expr), std::array<rank_type, sizeof ...(places)>>{std::forward<decltype(expr)>(expr), rank, {(rank_type)places...}};
    }
  }

}

#endif


