#ifndef PO_EXPR_BINARY_DIVIDE_BY_SCALAR_H
#define PO_EXPR_BINARY_DIVIDE_BY_SCALAR_H

#include "is_constant.h"
#include "is_expression.h"
#include "expr_constant.h"
#include "subexpr_type.h"

namespace po
{
  template<expression E1, constant E2>
  struct expr_binary_divide_by_constant
  {
    using _E1 = E1;
    using _E2 = E2;

    // using F1 = subexpr_type<E1>;
    // using F2 = subexpr_type<E2>;

    // F1 expr1;
    // F2 expr2;
    E1 expr1;
    E2 expr2;

    template<scalar ...X>
    scalar_type eval(X... x) const
    {
      return expr1.eval(x...) / expr2.eval(x...);
    }

    template<scalar ...X>
    scalar_type operator()(X... x) const
    {
      if(!ranks_compatible(expr1, expr2))
        return nan;

      return eval(x...);
    }
  };


  constexpr auto operator/(expression auto&& expr1, constant auto&& expr2)
  {
    return expr_binary_divide_by_constant{std::move(expr1), expr2};
  }
}

#endif

