#ifndef PO_IS_CONSTANT_H
#define PO_IS_CONSTANT_H

#include "is_scalar.h"
#include <concepts>
#include <type_traits>

namespace po
{
  struct expr_constant;

  template<typename Expr>
  concept is_constant =
    std::same_as<std::remove_cvref_t<Expr>, expr_constant> ||
    is_scalar<std::remove_cvref_t<Expr>>;

  template<typename Expr>
  concept constant = is_constant<Expr>;

}

#endif

