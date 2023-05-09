#ifndef PO_ACCUMULATE_MULT_H
#define PO_ACCUMULATE_MULT_H

#include "is_expr_binary_plus.h"
#include "is_expr_binary_minus.h"
#include "is_expr_binary_mult.h"

namespace po
{
  template<typename Expr>
  polynomial& accumulate_mult(polynomial& acc, Expr&& expr)
  {
    if constexpr(is_scalar<Expr>)
    {
      return acc.operator*=(expr);
    }

    if constexpr(is_constant<Expr>)
    {
      return acc.operator*=(expr.expr1);
    }

    if constexpr(is_polynomial<Expr>)
    {
      return acc.operator*=(expr);
    }

    if constexpr(is_expr_binary_mult<Expr>)
    {
      using namespace detail;

      if constexpr(P1<Expr>)
      {
        if constexpr(C2<Expr>)
        {
          return acc.operator*=(expr.expr1).operator*=(expr.expr2.expr1);
        }

        return acc.operator*=(expr.expr1).operator*=(expr.expr2);
      }

      if constexpr(P2<Expr>)
      {
        if constexpr(C1<Expr>)
        {
          return acc.operator*=(expr.expr2).operator*=(expr.expr1.expr1);
        }

        return acc.operator*=(expr.expr2).operator*=(expr.expr1);
      }
    }

    return acc.operator*=(instantiate(expr));
  }

}

#endif

