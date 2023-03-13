#ifndef PO_EXPR_UNARY_PLUS_H
#define PO_EXPR_UNARY_PLUS_H

#include "subexpr_type.h"

namespace po
{
  template<typename E1>
  struct expr_unary_plus
  {
    using _E1 = E1;
    using F1 = subexpr_type<E1>;
    F1 expr1;

    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      return expr1(x...);
    }
  };

  template<typename E>
  constexpr expr_unary_plus<E> operator+(E&& expr)
  {
    return {std::move(expr)};
  }

}

#endif

