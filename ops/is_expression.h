#ifndef PO_IS_EXPRESSION_H
#define PO_IS_EXPRESSION_H

#include "is_polynomial.h"
#include "is_constant.h"
#include "is_unary_expression.h"
#include "is_binary_expression.h"

namespace po
{
  template<typename Expr>
  concept is_expression =
    is_constant<Expr> ||
    is_polynomial<Expr> ||
    is_unary_expression<Expr> ||
    is_binary_expression<Expr>;

  template<typename Expr>
  concept expression = is_expression<Expr>;

}

#endif

