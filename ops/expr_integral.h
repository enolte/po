#ifndef PO_EXPR_INTEGRAL_H
#define PO_EXPR_INTEGRAL_H

#include "is_expression.h"
#include "../rank.h"
#include "../field.h"

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

  /*
   * polynomial p = ...., q = ....;
   * auto x = integral(D(p, 4) + q, 2, 2.3, 8.7);
   * const double y = x(1, 2, 3);
   *
   */
  template<expression E1>
  constexpr expr_integral<E1> integral(E1&& expr, rank_type place, scalar_type a, scalar_type b)
  {
    return expr_integral<E1>{std::move(expr), place, a, b};
  }

  template<expression E1>
  constexpr expr_integral<E1> integral(E1&& expr, rank_type place, interval&& i)
  {
    return expr_integral<E1>{std::move(expr), place, i.a, i.b};
  }

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
}


#endif


