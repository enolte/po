#ifndef PO_EXPR_BINARY_PLUS_H
#define PO_EXPR_BINARY_PLUS_H

#include "../field.h"

#include "is_expression.h"
#include "expr_constant.h"

namespace po
{
  template<typename E1, typename E2>
  struct expr_binary_plus
  {
    E1 expr1;
    E2 expr2;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return expr1(x...) + expr2(x...);
    }
  };

  template<typename E1, typename E2>
    requires is_expression<E1> && is_expression<E2>
  constexpr auto operator+(const E1& expr1, const E2& expr2)
  {
    if constexpr(supported_scalar_type<E2>)
      return expr_binary_plus<const E1&, const expr_constant>{expr1, expr_constant{expr2}};
    else if constexpr(supported_scalar_type<E1>)
      return expr_binary_plus<const expr_constant, const E2&>{expr_constant{expr1}, expr2};
    else
      return expr_binary_plus<const E1&, const E2&>{expr1, expr2};
  }

}

#endif

