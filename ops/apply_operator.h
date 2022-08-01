#ifndef PO_APPLY_OPERATOR_H
#define PO_APPLY_OPERATOR_H

#include "is_scalar.h"
#include "is_polynomial.h"

namespace po
{
  namespace pdo
  {
    template<typename OperatorExpr, typename ArgExpr>
      requires (!(is_scalar<OperatorExpr> || is_constant<OperatorExpr> || is_polynomial<OperatorExpr>))
    auto apply_operator(OperatorExpr&& expr, ArgExpr arg_expr)
    {
      return expr(arg_expr);
    }

    template<typename OperatorExpr, typename ArgExpr>
      requires is_scalar<OperatorExpr> || is_constant<OperatorExpr> || is_polynomial<OperatorExpr>
    auto apply_operator(OperatorExpr&& expr, ArgExpr&& arg_expr)
    {
      if constexpr(is_scalar<OperatorExpr> || is_constant<OperatorExpr>)
      {
        if constexpr(std::is_rvalue_reference_v<OperatorExpr>)
          return std::move(expr) * arg_expr;
        else
          return expr * arg_expr;
      }
      else
        return std::move(expr) * arg_expr;
    }
  }
}

#endif


