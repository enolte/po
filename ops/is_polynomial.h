#ifndef PO_IS_POLYNOMIAL_H
#define PO_IS_POLYNOMIAL_H

#include <concepts>
#include <type_traits>

namespace po
{
  struct polynomial;

  template<typename Expr>
  concept is_polynomial = std::same_as<std::remove_cvref_t<Expr>, polynomial>;
}

#endif

