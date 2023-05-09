#ifndef PO_ACCUMULATE_SUB_H
#define PO_ACCUMULATE_SUB_H

#include "is_expr_binary_plus.h"
#include "is_expr_binary_minus.h"
#include "is_expr_binary_mult.h"

namespace po
{
  template<typename Expr>
  polynomial& accumulate_sub(polynomial& acc, Expr&& expr)
  {
    if constexpr(is_constant<Expr>)
    {
      return acc.operator-=(expr.expr1);
    }

    if constexpr(is_polynomial<Expr>)
    {
      return acc.operator-=(expr);
    }

    if constexpr(is_expr_binary_plus<Expr>)
    {
      using namespace detail;

      if constexpr(P1<Expr> && P2<Expr>)
      {
        if(&acc != &expr.expr1 && &acc != &expr.expr2)
        {
          return acc.operator-=(expr.expr1).operator-=(expr.expr2);
        }

        if(&acc == &expr.expr1 && &acc != &expr.expr2)
        {
          return acc.operator*=(2).operator-=(expr.expr2);
        }

        if(&acc != &expr.expr1 && &acc == &expr.expr2)
        {
          return (acc = expr.expr1).operator*=(-1);
        }

        if(&acc == &expr.expr1 && &acc == &expr.expr2)
        {
          return acc;
        }
      }

      // TODO Test
      if constexpr(P1<Expr> && C2<Expr>)
      {
        if(&acc == &expr.expr1)
          return (acc = -expr.expr2.expr1);
        else
          return (acc -= expr.expr1) -= expr.expr2.expr1;
      }

      // TODO Test
      if constexpr(C1<Expr> && P2<Expr>)
      {
        if(&acc == &expr.expr2)
          return (acc = -expr.expr1.expr1);
        else
          return (acc -= expr.expr1.expr1) -= expr.expr2;
      }
    }

    if constexpr(is_expr_binary_minus<Expr>)
    {
      using namespace detail;

      if constexpr(P1<Expr> && P2<Expr>)
      {
        if(&acc == &expr.expr1 && &acc == &expr.expr2)
        {
          return acc;
        }

        if(&acc != &expr.expr1 && &acc != &expr.expr2)
        {
          return acc.operator-=(expr.expr1).operator+=(expr.expr2);
        }

        if(&acc == &expr.expr1 && &acc != &expr.expr2)
        {
          return acc = expr.expr2;
        }

        if(&acc != &expr.expr1 && &acc == &expr.expr2)
        {
          return acc.operator*=(2).operator-=(expr.expr1);
        }
      }

      // TODO Test
      if constexpr(P1<Expr> && C2<Expr>)
      {
        if(&acc == &expr.expr1)
          return (acc = expr.expr2.expr1);
        else
          return (acc -= expr.expr1) += expr.expr2.expr1;
      }

      // TODO Test
      if constexpr(C1<Expr> && P2<Expr>)
      {
        if(&acc == &expr.expr2)
          return (acc *= 2) -= expr.expr1.expr1;
        else
          return (acc -= expr.expr1.expr1) += expr.expr2;
      }
    }

    return acc.operator-=(instantiate(expr));
  }

}

#endif

