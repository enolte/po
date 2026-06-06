#ifndef PO_IS_EXPR_BINARY_MULT_H
#define PO_IS_EXPR_BINARY_MULT_H

#include "is_binary_expression.h"
#include <type_traits>

namespace po
{
  template<typename>
  struct is_expr_binary_mult_type : std::false_type {};

  template<expression E1, expression E2>
  struct is_expr_binary_mult_type<expr_binary_mult<E1, E2>> : std::true_type {};

  template<typename E>
  concept is_expr_binary_mult = is_expr_binary_mult_type<std::remove_cvref_t<E>>::value;
}

#endif
