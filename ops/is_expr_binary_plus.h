#ifndef PO_IS_EXPR_BINARY_PLUS_H
#define PO_IS_EXPR_BINARY_PLUS_H

#include "is_binary_expression.h"
#include <type_traits>

namespace po
{
  template<typename>
  struct is_expr_binary_plus_type : std::false_type {};

  template<expression E1, expression E2>
  struct is_expr_binary_plus_type<expr_binary_plus<E1, E2>> : std::true_type {};

  template<typename E>
  concept is_expr_binary_plus = is_expr_binary_plus_type<std::remove_cvref_t<E>>::value;
}

#endif
