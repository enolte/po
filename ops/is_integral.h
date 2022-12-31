#ifndef PO_IS_INTEGRAL_H
#define PO_IS_INTEGRAL_H

#include "is_unary_expression.h"

namespace po
{
  template<typename Expr>
  concept is_integral =
    is_unary_expression<Expr> &&
    requires(Expr e)
    {
      e.b;
      e.a;
      e.place;
    };

  // template<typename Expr>
  // concept integral = is_integral<Expr>;

}

#endif

