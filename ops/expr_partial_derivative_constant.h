#ifndef PO_EXPR_PARTIAL_DERIVATIVE_CONSTANT_H
#define PO_EXPR_PARTIAL_DERIVATIVE_CONSTANT_H

#include "expr_constant.h"

namespace po
{
  namespace detail
  {
    template<typename E1>
    struct expr_partial_derivative_constant
    {
      using _E1 = E1;
      using F1 = subexpr_type<E1>;

      const F1 expr1;
      const rank_type place;

      template<typename ...X>
      scalar_type operator()(X... x) const
      {
        return scalar_type{0};
      }
    };
  }

  template<>
  struct expr_partial_derivative<scalar_type>
  : detail::expr_partial_derivative_constant<scalar_type>
  {};

  template<>
  struct expr_partial_derivative<scalar_type&>
  : detail::expr_partial_derivative_constant<scalar_type&>
  {};

  template<>
  struct expr_partial_derivative<const scalar_type&>
  : detail::expr_partial_derivative_constant<scalar_type>
  {};

  template<>
  struct expr_partial_derivative<expr_constant>
  : detail::expr_partial_derivative_constant<expr_constant>
  {};

  template<>
  struct expr_partial_derivative<expr_constant&>
  : detail::expr_partial_derivative_constant<expr_constant&>
  {};

  template<>
  struct expr_partial_derivative<const expr_constant&>
  : detail::expr_partial_derivative_constant<const expr_constant&>
  {};

}

#endif

