#ifndef PO_EXPR_EXTEND_POLYNOMIAL_H
#define PO_EXPR_EXTEND_POLYNOMIAL_H

#include "../types/rank.h"

#include <array>
#include <algorithm>

namespace po
{
  namespace detail
  {
    template<is_polynomial E1, typename Places>
    struct expr_extend
    {
      using _E1 = E1;
      using F1 = subexpr_type<E1>;

      const F1 expr1;
      const rank_type rank;
      const Places places;

      template<scalar...X>
      constexpr scalar_type eval(X... x) const
      {
        return operator()(x...);
      }

      template<scalar...X>
      constexpr scalar_type operator()(X... x) const
      {
        if(rank != sizeof ...(X))
          // Error condition
          return nan;

        if(places.size() != expr1.rank())
          // Error condition
          return nan;

        if(!std::ranges::all_of(places, [this](const rank_type& place){ return place < rank; }))
          // Error condition
          return nan;

        double acc = 0.;
        for(const auto& t : expr1.terms)
        {
          acc += t(places, x...);
        }

        return acc;
      }
    };
  }

  template<typename Places>
  struct expr_extend<const polynomial&, Places>
  : detail::expr_extend<const polynomial&, Places>
  {};

  template<typename Places>
  struct expr_extend<polynomial&, Places>
  : detail::expr_extend<polynomial&, Places>
  {};

}


#endif


