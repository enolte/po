#ifndef PO_IS_UNARY_EXPRESSION_H
#define PO_IS_UNARY_EXPRESSION_H

#include <concepts>
#include <type_traits>

namespace po
{
  template<typename Expr>
  concept is_unary_expression =
    requires(Expr e)
    {
      e.expr1;

      e();
    };
}

#endif

