#ifndef PO_IS_BINARY_EXPRESSION_H
#define PO_IS_BINARY_EXPRESSION_H

#include <concepts>
#include <type_traits>

namespace po
{
  template<typename Expr>
  concept is_binary_expression =
    requires(Expr e)
    {
      e.expr1;
      e.expr2;

      e();
    };
}

#endif

