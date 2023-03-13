#ifndef PO_EXPR_BINARY_PLUS_H
#define PO_EXPR_BINARY_PLUS_H

#include "is_scalar.h"
#include "is_expression.h"
#include "expr_constant.h"
#include "subexpr_type.h"

namespace po
{
  template<expression E1, expression E2>
  struct expr_binary_plus
  {
    using _E1 = E1;
    using _E2 = E2;

    using F1 = subexpr_type<E1>;
    using F2 = subexpr_type<E2>;

    F1 expr1;
    F2 expr2;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return expr1(x...) + expr2(x...);
    }
  };


  template<expression E1, expression E2>
  constexpr auto operator+(E1&& expr1, E2&& expr2)
  {
    if constexpr(is_scalar<E2>)
      return expr_binary_plus<E1, expr_constant>{std::move(expr1), expr_constant{expr2}};
    else if constexpr(is_scalar<E1>)
      return expr_binary_plus<expr_constant, E2>{expr_constant{expr1}, std::move(expr2)};
    else
      return expr_binary_plus<E1, E2>{std::move(expr1), std::move(expr2)};
  }
}

#endif

