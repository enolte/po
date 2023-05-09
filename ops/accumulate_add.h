#ifndef PO_ACCUMULATE_ADD_H
#define PO_ACCUMULATE_ADD_H

#include "is_expr_binary_plus.h"
#include "is_expr_binary_minus.h"
#include "is_expr_binary_mult.h"

namespace po
{
  namespace detail
  {
    template<typename X> concept P1 = po::is_polynomial<typename X::_E1>;
    template<typename X> concept P2 = po::is_polynomial<typename X::_E2>;

    template<typename X> concept S1 = po::is_scalar<typename X::_E1>;
    template<typename X> concept S2 = po::is_scalar<typename X::_E2>;

    template<typename X> concept C1 = po::is_constant<typename X::_E1>;
    template<typename X> concept C2 = po::is_constant<typename X::_E2>;
  }

  template<typename Expr>
  polynomial& accumulate_add(polynomial& acc, Expr&& expr)
  {
    if constexpr(is_constant<Expr>)
    {
      return acc.operator+=(expr.expr1);
    }

    if constexpr(is_polynomial<Expr>)
    {
      return acc.operator+=(expr);
    }

    if constexpr(is_expr_binary_plus<Expr>)
    {
      using namespace detail;

      if constexpr(P1<Expr> && P2<Expr>)
      {
        if(&acc != &expr.expr1 && &acc != &expr.expr2)
        {
          return acc.operator+=(expr.expr1).operator+=(expr.expr2);
        }

        if(&acc == &expr.expr1 && &acc != &expr.expr2)
        {
          return acc.operator*=(2).operator+=(expr.expr2);
        }

        if(&acc != &expr.expr1 && &acc == &expr.expr2)
        {
          return acc.operator*=(2).operator+=(expr.expr1);
        }

        if(&acc == &expr.expr1 && &acc == &expr.expr2)
        {
          return acc.operator*=(3);
        }
      }

      if constexpr(P1<Expr> && C2<Expr>)
      {
        if(&acc == &expr.expr1)
          return (acc *= 2) += expr.expr2.expr1;
        else
          return (acc += expr.expr1) += expr.expr2.expr1;
      }

      if constexpr(C1<Expr> && P2<Expr>)
      {
        if(&acc == &expr.expr2)
          return (acc *= 2) += expr.expr1.expr1;
        else
          return (acc += expr.expr1.expr1) += expr.expr2;
      }
    }

    if constexpr(is_expr_binary_minus<Expr>)
    {
      using namespace detail;

      if constexpr(P1<Expr> && P2<Expr>)
      {
        if(&expr.expr1 == &expr.expr2)
        {
          return acc;
        }

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
          return acc = expr.expr1;
        }
      }
    }

    // TODO Test
    if constexpr(is_expr_binary_mult<Expr>)
    {
      using namespace detail;

      if constexpr(P1<Expr> && P2<Expr>)
      {
        if(&acc == &expr.expr1 && &acc != &expr.expr2)
        {
          return acc.operator+=(1).operator*=(expr.expr2);
        }

        if(&acc != &expr.expr1 && &acc == &expr.expr2)
        {
          return acc.operator+=(1).operator*=(expr.expr1);
        }
      }
    }

    return acc.operator+=(instantiate(expr));
  }


}

#endif