#ifndef PO_EXPR_EXTEND_CONSTANT_H
#define PO_EXPR_EXTEND_CONSTANT_H

#include "../types/rank.h"
#include <algorithm>

namespace po
{
  namespace detail
  {
    template<constant E1, typename Places>
    struct expr_extend_constant
    {
      using _E1 = E1;
      using F1 = subexpr_type<E1>;

      const F1 expr1;
      const rank_type rank;
      const Places places;

      template<typename ...X>
      constexpr scalar_type operator()(X... x) const
      {
        if(rank != sizeof ...(X))
          // Error condition
          return nan;

        if(places.size() != 0)
          // Error condition
          return nan;

        if(!std::ranges::all_of(places, [this](const rank_type& place){ return place < rank; }))
          // Error condition
          return nan;

        return expr1.expr1;
      }
    };
  }

  template<typename Places>
  struct expr_extend<const expr_constant&, Places>
  : detail::expr_extend_constant<const expr_constant&, Places>
  {};

  template<typename Places>
  struct expr_extend<expr_constant&, Places>
  : detail::expr_extend_constant<expr_constant&, Places>
  {};

  template<typename Places>
  struct expr_extend<expr_constant, Places>
  : detail::expr_extend_constant<expr_constant&, Places>
  {};

  namespace detail
  {
    template<scalar E1, typename Places>
    struct expr_extend_scalar
    {
      using _E1 = E1;
      using F1 = subexpr_type<E1>;

      const F1 expr1;
      const rank_type rank;
      const Places places;

      template<typename ...X>
      constexpr scalar_type operator()(X... x) const
      {
        if(rank != sizeof ...(X))
          // Error condition
          return nan;

        if(places.size() != 0)
          // Error condition
          return nan;

        if(!std::ranges::all_of(places, [this](const rank_type& place){ return place < rank; }))
          // Error condition
          return nan;

        return expr1;
      }
    };
  }

  template<typename Places>
  struct expr_extend<const scalar_type&, Places>
  : detail::expr_extend_scalar<const scalar_type&, Places>
  {};

  template<typename Places>
  struct expr_extend<scalar_type&, Places>
  : detail::expr_extend_scalar<scalar_type&, Places>
  {};

  template<typename Places>
  struct expr_extend<scalar_type, Places>
  : detail::expr_extend_scalar<scalar_type, Places>
  {};
}


#endif


