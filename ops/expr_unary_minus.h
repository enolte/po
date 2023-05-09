#ifndef PO_EXPR_UNARY_MINUS_H
#define PO_EXPR_UNARY_MINUS_H

#include "subexpr_type.h"

namespace po
{
  template<typename E1>
  struct expr_unary_minus
  {
    using _E1 = E1;
    using F1 = subexpr_type<E1>;
    F1 expr1;

    template<scalar... X>
    scalar_type eval(X... x) const
    {
      return scalar_type{-1} * expr1(x...);
    }

    template<scalar...X>
    scalar_type operator()(X... x) const
    {
      return scalar_type{-1} * expr1(x...);
    }
  };

  template<typename E>
  constexpr expr_unary_minus<E> operator-(E&& expr)
  {
    return {std::move(expr)};
  }

}

#endif


