#ifndef PO_IS_NULLARY_EXPRESSION_H
#define PO_IS_NULLARY_EXPRESSION_H

#include "is_unary_expression.h"

namespace po
{
  template<typename Expr>
  concept is_nullary_expression =
    is_polynomial<Expr> || is_constant<Expr>;
}

#endif

