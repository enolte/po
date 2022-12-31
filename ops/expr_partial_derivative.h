#ifndef PO_EXPR_PARTIAL_DERIVATIVE_H
#define PO_EXPR_PARTIAL_DERIVATIVE_H

namespace po
{
  template<expression>
  struct expr_partial_derivative;
}

// Specializations of expr_partial_derivative
#include "expr_partial_derivative_constant.h"
#include "expr_partial_derivative_polynomial.h"
#include "expr_partial_derivative_binary_plus.h"
#include "expr_partial_derivative_binary_minus.h"
#include "expr_partial_derivative_binary_mult.h"
#include "expr_partial_derivative_unary_plus.h"
#include "expr_partial_derivative_unary_minus.h"
#include "expr_partial_derivative_integral.h"
#include "expr_partial_derivative2.h"

namespace po
{
  /*
   * polynomial p = ...., q = ....;
   * D(p - 5*q, 4);
   *
   */
  template<expression E1>
  constexpr expr_partial_derivative<E1> D(E1&& expr, rank_type place)
  {
    return expr_partial_derivative<E1>{std::move(expr), place};
  }
}


#endif


