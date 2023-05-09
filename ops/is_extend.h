#ifndef PO_IS_EXTEND_H
#define PO_IS_EXTEND_H

#include "is_unary_expression.h"

namespace po
{
  template<typename Expr>
  concept is_extend =
    is_unary_expression<Expr> &&
    requires(Expr e)
    {
      e.rank;
      e.places;
    };
}

#endif

