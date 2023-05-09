#ifndef PO_INSTANTIATE_H
#define PO_INSTANTIATE_H

#include "instantiate_constant.h"
#include "instantiate_polynomial.h"
#include "instantiate_unary_plus.h"
#include "instantiate_unary_minus.h"
#include "instantiate_binary_plus.h"
#include "instantiate_binary_minus.h"
#include "instantiate_binary_mult.h"
#include "instantiate_partial_derivative.h"
#include "instantiate_integral.h"
#include "instantiate_antiderivative.h"
#include "instantiate_extend.h"

namespace po
{
  template<expression Expr>
  polynomial instantiate(Expr&& expr, rank_type rank)
  {
    polynomial p = zero(rank);
    instantiate(p, std::move(expr), rank);
    return p;
  }

  template<expression Expr>
  polynomial instantiate(Expr&& expr)
  {
    const rank_type rank = expr_rank(expr);
    return instantiate(std::move(expr), rank);
  }
}

#endif

