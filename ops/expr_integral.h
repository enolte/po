#ifndef PO_EXPR_INTEGRAL_H
#define PO_EXPR_INTEGRAL_H

#include "is_expression.h"
#include "../types/rank.h"
#include "../types/scalar.h"

namespace po
{
  template<expression>
  struct expr_integral;
}

// Specializations of expr_integral
#include "expr_integral_constant.h"
#include "expr_integral_polynomial.h"
#include "expr_integral_binary_plus.h"
#include "expr_integral_binary_minus.h"
#include "expr_integral_binary_mult.h"
#include "expr_integral_unary_minus.h"
#include "expr_integral_unary_plus.h"
#include "expr_integral_partial_derivative.h"
#include "expr_integral_antiderivative.h"
#include "expr_integral2.h"

namespace po
{
  struct interval
  {
    scalar_type a, b;
  };

  struct parametric_interval
  {
    rank_type place;
    interval&& i;
  };

  using place = parametric_interval;

  /*
   * polynomial p = ...., q = ....;
   * auto x = integral(D(p, 4) + q, {2, {2.3, 8.7}});
   * const double y = x(1, 2, 3);
   *
   */
  template<expression E1>
  constexpr expr_integral<E1> integral(E1&& expr, parametric_interval&& i)
  {
    return expr_integral<E1>{std::move(expr), i.place, i.i.a, i.i.b};
  }

  template<expression E1>
  constexpr expr_integral<E1> integral(E1&& expr, const parametric_interval& i)
  {
    return expr_integral<E1>{std::move(expr), i.place, i.i.a, i.i.b};
  }

  template<expression E1, typename ParametricInterval0, typename ...ParametricInterval>
  constexpr auto integral(E1&& expr, ParametricInterval0&& i0, ParametricInterval&&... i)
  {
    if constexpr (sizeof ...(i) > 0)
    {
      return integral(integral(std::forward<E1>(expr), i0), std::forward<ParametricInterval>(i)...);
    }
    else
    {
      return expr_integral<E1>{std::forward<E1>(expr), i0.place, i0.i.a, i0.i.b};
    }
  }

}


#endif


