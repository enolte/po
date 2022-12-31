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

namespace po
{
  template<typename Expr>
  polynomial instantiate(Expr&& expr, rank_type rank)
  {
    polynomial p = polynomial::make_zero(rank);
    instantiate(p, std::move(expr), rank);
    return p;
  }
#if 1
  // TODO Further testing
  template<typename Expr>
  polynomial instantiate(Expr&& expr)
  {
    return instantiate(std::move(expr), expr_rank(expr));
  }
#endif
}

#endif

