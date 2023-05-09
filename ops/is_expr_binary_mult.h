#ifndef PO_IS_EXPR_BINARY_MULT_H
#define PO_IS_EXPR_BINARY_MULT_H

#include "is_binary_expression.h"

namespace po
{
  template<typename E>
  concept is_expr_binary_mult=
    is_binary_expression<E> &&
    std::same_as<E, expr_binary_mult<typename E::_E1, typename E::_E2>>;
}

#endif


