#ifndef PO_EXPR_EXTEND_H
#define PO_EXPR_EXTEND_H

#include <array>

#include "is_expression.h"
#include "../types/rank.h"

namespace po
{
  template<expression, typename Places>
  struct expr_extend;

  template<std::size_t ...Places>
  using places = std::array<rank_type, sizeof ...(Places)>;

  template<expression E, std::integral... Places>
  expr_extend(E&&, rank_type, Places...) -> expr_extend<E, std::array<rank_type, sizeof ...(Places)>>;
  // TODO gcc 13.1.0 does not accept this.
  // expr_extend(E&&, rank_type, Places...) -> expr_extend<E, places<sizeof ...(Places)>>;

  template<expression E, std::size_t n>
  expr_extend(E&&, rank_type, places<n>&&) -> expr_extend<E, places<n>>;
}

// Specializations of expr_extend
#include "expr_extend_constant.h"
#include "expr_extend_polynomial.h"
// TODO
// #include "expr_extend_binary_plus.h"
// #include "expr_extend_binary_minus.h"
// #include "expr_extend_binary_mult.h"
// #include "expr_extend_unary_minus.h"
// #include "expr_extend_unary_plus.h"
// #include "expr_extend_partial_derivative.h"
// #include "expr_extend_antiderivative.h"
// #include "expr_extend_integral.h"
// #include "expr_extend2.h"

namespace po
{
  /*
   * Extend the signature of the given expression to the given rank,
   * by using the values of the numerical arguments at the given places.
   *
   * The param pack Places defines a parameter map from the source expression signature
   * to the destination signature.
   *
   * auto x = extend(p*q, 6, 0, 2);
   * auto x = extend(p - 3*q, 8, 3, 5);
   * auto x = extend(p - 3*q, rank<8>{}, 3, 5);
   * etc.
   *
   * assumes: Values in places... are distinct, and all < rank.
   */
  template<expression E1, typename ...Places>
    requires ( ... && std::integral<std::remove_cvref_t<Places>>)
  constexpr auto extend(E1&& expr, rank_type rank, Places... places)
  {
    return expr_extend{
      std::forward<E1>(expr),
      rank,
      (rank_type)places...};
  }

  // TODO Test
  template<expression E1, std::size_t n>
  constexpr auto extend(E1&& expr, rank_type rank, const po::places<n>& places)
  {
    return expr_extend{
      std::forward<E1>(expr),
      rank,
      places};
  }

  // TODO Test
  template<expression E1>
  constexpr auto extend(E1&& expr, rank_type rank, std::initializer_list<rank_type>&& places)
  {
    return expr_extend{
      std::forward<E1>(expr),
      rank,
      std::array{places}};
  }

}

#endif


