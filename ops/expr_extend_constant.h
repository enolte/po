#ifndef PO_EXPR_EXTEND_CONSTANT_H
#define PO_EXPR_EXTEND_CONSTANT_H

#include "../types/rank.h"
#include <algorithm>

namespace po
{
  namespace detail
  {
    template<constant E1>
    struct expr_extend_constant
    {
      using F1 = subexpr_type<E1>;

      const F1 expr1;
      const rank_type rank;
      // const Places places;

      template<typename ...X>
      constexpr scalar_type operator()(X... x) const
      {
        if(rank != sizeof ...(X))
          // Error condition
          return nan;

        // return expr1.expr1;
        if constexpr(scalar<E1>)
          return expr1;
        else if constexpr(constant<E1>)
          return expr1.expr1;
      }
    };
  }

  template<>
  struct expr_extend<scalar_type>
  : detail::expr_extend_constant<scalar_type>
  {};
/*
  template<>
  struct expr_extend<const expr_constant&>
  : detail::expr_extend_constant<const expr_constant&>
  {};

  template<>
  struct expr_extend<expr_constant&>
  : detail::expr_extend_constant<expr_constant&>
  {};

  template<>
  struct expr_extend<expr_constant>
  : detail::expr_extend_constant<expr_constant&>
  {};

  namespace detail
  {
    template<scalar E1>
    struct expr_extend_scalar
    {
      using F1 = subexpr_type<E1>;

      const F1 expr1;
      const rank_type rank;
      // const Places places;

      template<typename ...X>
      constexpr scalar_type operator()(X... x) const
      {
        if(rank != sizeof ...(X))
          // Error condition
          return nan;

        return expr1;
      }
    };
  }

  template<>
  struct expr_extend<scalar_type>
  : detail::expr_extend_scalar<scalar_type>
  {};
*/
}


#endif


