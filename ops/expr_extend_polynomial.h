#ifndef PO_EXPR_EXTEND_POLYNOMIAL_H
#define PO_EXPR_EXTEND_POLYNOMIAL_H

#include "../types/rank.h"

#include <algorithm>

namespace po
{
  namespace detail
  {
    template<is_polynomial E1, typename Places>
    struct expr_extend
    {
      using F1 = subexpr_type<E1>;

      const F1 expr1;
      const rank_type rank;
      const Places places;

      constexpr scalar_type eval(scalar auto... x) const
      {
        return operator()(x...);
      }

   private:
      template<std::size_t... n>
      constexpr scalar_type eval(std::index_sequence<n...>, scalar_type* xx) const
      // constexpr scalar_type eval(scalar auto... x) const
      {
        return expr1(xx[n]...);

        // if constexpr(sizeof ...(x) < expr1.rank)
        // {
        //   return 1.;
        // }
        // else
        // {
        //   return expr(x...);
        // }

        // const auto set_value = [](double x)
        // {
        //   if(i == places[j])
        //   {
        //     xx[j] = x;
        //   }
        // };
      }

    public:

      constexpr scalar_type operator()(scalar auto... x) const
      {
        if(rank != sizeof ...(x))
          // Error condition
          return nan;
        
        double xx[expr_rank(expr1)]{};
        std::size_t i{};
        auto set_expr_args = [&, this](double x)
        {
            if(const auto found{ std::ranges::find(places, i) }; found != std::cend(places))
            {
              xx[i] = x;
              ++i;
            }
        };

        (set_expr_args(x), ...);

        // // TODO 11:21 Monday, November 2, 2026.`places` is not compile-time defined. I need something
        // // like an index_sequence for `xx`, not `x...`. This doesn't work yet.
        // return eval(std::index_sequence_for<decltype(x)...>{}, xx);

        auto ixx = std::make_index_sequence<expr_rank(expr1)>{};
        return eval(ixx, xx);
        // std::index_sequence_for<X...> ix{};
        // return expr1(x)

/*
        // return eval(std::index_sequence<sizeof ...(x)>{}, x...);

        // std::array<scalar_type, expr1.rank()> xx{};

        // std::size_t i{}, j{};
        // const auto set_value = [&i, &j](double x)
        // {
        //   if(i == places[j])
        //   {
        //     xx[j] = x;
        //   }
        // };

        // return expr1(xx);
PO_LINE;
        // if(places.size() != expr1.rank())
        //   // Error condition
        //   return nan;

        if(!std::ranges::all_of(places, [this](const rank_type& place){ return place < rank; }))
          // Error condition
          return nan;
PO_LINE;
        double acc = 0.;
        for(const auto& t : expr1.terms)
        {
          acc += t(places, x...);
        }
PO_LINE;
PO_TRACE(acc);
        return acc;
*/
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


