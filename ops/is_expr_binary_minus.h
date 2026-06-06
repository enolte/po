#ifndef PO_IS_EXPR_BINARY_MINUS_H
#define PO_IS_EXPR_BINARY_MINUS_H

#include "is_binary_expression.h"
#include <type_traits>

namespace po
{
  template<typename>
  struct is_expr_binary_minus_type : std::false_type {};

  template<expression E1, expression E2>
  struct is_expr_binary_minus_type<expr_binary_minus<E1, E2>> : std::true_type {};

  template<typename E>
  concept is_expr_binary_minus = is_expr_binary_minus_type<std::remove_cvref_t<E>>::value;
}

#endif
