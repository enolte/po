#ifndef PO_IS_UNARY_EXPRESSION_H
#define PO_IS_UNARY_EXPRESSION_H

#include "is_binary_expression.h"

namespace po
{
  template<typename Expr>
  concept is_unary_expression =
    !is_binary_expression<Expr> &&
    requires(Expr e)
    {
      e.expr1;
    };
}

#endif

