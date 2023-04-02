#ifndef PO_EXPR_INTEGRAL_CONSTANT_H
#define PO_EXPR_INTEGRAL_CONSTANT_H

#include "expr_constant.h"

namespace po
{
  namespace detail
  {
    template<typename T>
    struct expr_integral_constant
    {
      using _E1 = T;
      using F1 = subexpr_type<T>;

      const F1 expr1;
      const rank_type place;
      const scalar_type a, b;

      template<typename ...X>
      scalar_type operator()(X... x) const
      {
        return expr1.expr1 * (b - a);
      }
    };

  }

  template<>
  struct expr_integral<expr_constant> : detail::expr_integral_constant<expr_constant> {};

  template<>
  struct expr_integral<expr_constant&> : detail::expr_integral_constant<expr_constant&> {};

  namespace detail
  {
    template<typename T>
    struct expr_integral_scalar
    {
      using _E1 = T;
      using F1 = subexpr_type<T>;

      const F1 expr1;
      const rank_type place;
      const scalar_type a, b;

      template<typename ...X>
      scalar_type operator()(X... x) const
      {
        return expr1 * (b - a);
      }
    };

  }

  template<>
  struct expr_integral<scalar_type> : detail::expr_integral_scalar<scalar_type> {};

  template<>
  struct expr_integral<scalar_type&> : detail::expr_integral_scalar<scalar_type&> {};

  template<>
  struct expr_integral<const scalar_type&> : detail::expr_integral_scalar<scalar_type&> {};

}

#endif

