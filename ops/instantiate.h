#ifndef PO_INSTANTIATE_H
#define PO_INSTANTIATE_H

#if 1
#include "instantiate_constant.h"
#include "instantiate_binary_plus.h"
#include "instantiate_unary_plus.h"
#include "instantiate_unary_minus.h"
#include "instantiate_polynomial.h"
#include "instantiate_binary_minus.h"
#include "instantiate_binary_mult.h"
#endif

#if 0
#include "../polynomial.h"
#include "is_expression.h"

#include "expr_binary_plus.h"
#include "expr_binary_mult.h"
#include "expr_binary_minus.h"

#include "expr_unary_minus.h"
#include "expr_unary_plus.h"

#include "../ostream/polynomial_ostream.h"
#include "../test/macros.h"
#endif

namespace po
{
#if 0
  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, expr_binary_plus<E1, E2>&& expr, Rank&&);

  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_binary_plus<E1, E2>& expr, Rank&&);

  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, expr_binary_minus<E1, E2>&& expr, Rank&&);

  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_binary_minus<E1, E2>& expr, Rank&&);

  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, expr_binary_mult<E1, E2>&& expr, Rank&&);

  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_binary_mult<E1, E2>& expr, Rank&&);

  template<typename E1, typename Rank>
  polynomial& instantiate(polynomial& p, expr_unary_plus<E1>&& expr, Rank&&);

  template<typename E1, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_unary_plus<E1>& expr, Rank&&);

  template<typename E1, typename Rank>
  polynomial& instantiate(polynomial& p, expr_unary_minus<E1>&& expr, Rank&&);

  template<typename E1, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_unary_minus<E1>& expr, Rank&&);

  template<typename Rank>
  polynomial& instantiate(polynomial& p, const expr_constant& expr, Rank&&);

  template<typename Rank>
  polynomial& instantiate(polynomial& p, const polynomial& expr, Rank&&);
#endif

  template<typename Expr, typename Rank>
  polynomial instantiate(Expr&& expr, Rank&&)
  {
    // PO_TRACE("entry point");
    polynomial p{Rank{}};
    instantiate(p, std::move(expr), Rank{});
    // PO_TRACE("entry point: p = " << p);
    // std::cout << "entry point: p = " << p << std::endl;
    return p;
  }

#if 0
  template<typename E1, typename Rank>
  polynomial& instantiate(polynomial& p, expr_unary_plus<E1>&& expr, Rank&&)
  {
    // PO_LINE;
    instantiate(p, expr.expr1, Rank{});
    return p;
  }

  template<typename E1, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_unary_plus<E1>& expr, Rank&&)
  {
    // PO_LINE;
    instantiate(p, expr.expr1, Rank{});
    return p;
  }

  template<typename E1, typename Rank>
  polynomial& instantiate(polynomial& p, expr_unary_minus<E1>&& expr, Rank&&)
  {
    // PO_LINE;
    instantiate(p, expr.expr1, Rank{});
    for(auto& t : p.terms)
      t.coefficient = -t.coefficient;
    return p;
  }

  template<typename E1, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_unary_minus<E1>& expr, Rank&&)
  {
    // PO_LINE;
    instantiate(p, expr.expr1, Rank{});
    for(auto& t : p.terms)
      t.coefficient = -t.coefficient;
    return p;
  }

  template<typename Rank>
  polynomial& instantiate(polynomial& p, const expr_constant& expr, Rank&&)
  {
    // PO_LINE; PO_TRACE("terminal: scalar = " << expr.expr1);
    p = polynomial(expr.expr1, Rank{});
    return p;
  }

  template<typename Rank>
  polynomial& instantiate(polynomial& p, const polynomial& expr, Rank&&)
  {
    // PO_LINE; PO_TRACE("terminal: polynomial = " << expr);
    p = expr;
    return p;
  }

  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, expr_binary_plus<E1, E2>&& expr, Rank&&)
  {
    // PO_LINE;
    polynomial right{Rank{}};
    instantiate(right, expr.expr2, Rank{});
    instantiate(p, expr.expr1, Rank{});

    p += right;

    return p;
  }

  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_binary_plus<E1, E2>& expr, Rank&&)
  {
    // PO_LINE;
    polynomial right{Rank{}};
    instantiate(right, expr.expr2, Rank{});
    instantiate(p, expr.expr1, Rank{});

    p += right;

    return p;
  }

  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, expr_binary_minus<E1, E2>&& expr, Rank&&)
  {
    // PO_LINE;
    instantiate(p, expr.expr1, Rank{});
    polynomial right{Rank{}};
    instantiate(right, expr.expr2, Rank{});

    p -= right;

    return p;
  }

  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_binary_minus<E1, E2>& expr, Rank&&)
  {
    // PO_LINE;
    instantiate(p, expr.expr1, Rank{});
    polynomial right{Rank{}};
    instantiate(right, expr.expr2, Rank{});

    p -= right;

    return p;
  }

  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, expr_binary_mult<E1, E2>&& expr, Rank&&)
  {
    // PO_LINE;
    polynomial right{Rank{}};
    instantiate(p, expr.expr1, Rank{});
    instantiate(right, expr.expr2, Rank{});

    p *= right;

    return p;
  }

  template<typename E1, typename E2, typename Rank>
  polynomial& instantiate(polynomial& p, const expr_binary_mult<E1, E2>& expr, Rank&&)
  {
    // PO_LINE;
    polynomial right{Rank{}};
    instantiate(p, expr.expr1, Rank{});
    instantiate(right, expr.expr2, Rank{});

    p *= right;

    return p;
  }
#endif
}


#endif