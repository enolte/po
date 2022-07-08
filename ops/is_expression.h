#ifndef PO_IS_EXPRESSION_H
#define PO_IS_EXPRESSION_H

#include "../field.h"
#include "is_polynomial.h"
#include "is_unary_expression.h"
#include "is_binary_expression.h"

namespace po
{
  template<typename Expr>
  concept is_expression =
    supported_scalar_type<Expr> ||
    is_polynomial<Expr> ||
    is_unary_expression<Expr> ||
    is_binary_expression<Expr>;
}

#endif

