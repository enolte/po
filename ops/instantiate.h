#ifndef PO_INSTANTIATE_H
#define PO_INSTANTIATE_H

#include "instantiate_constant.h"
#include "instantiate_unary_plus.h"
#include "instantiate_unary_minus.h"
#include "instantiate_polynomial.h"
#include "instantiate_binary_plus.h"
#include "instantiate_binary_minus.h"
#include "instantiate_binary_mult.h"
#include "instantiate_partial_derivative.h"

namespace po
{
  template<typename Expr, typename Rank>
  polynomial instantiate(Expr&& expr, Rank&&)
  {
    polynomial p{Rank{}};
    instantiate(p, std::move(expr), Rank{});
    return p;
  }
}

#endif

