#ifndef PO_ANTIDERIVATIVE_A_H
#define PO_ANTIDERIVATIVE_A_H

namespace po
{
  template<expression E1, typename ...Places>
  constexpr auto A(E1&& expr, rank_type place, Places&&... places)
  {
    return antiderivative(std::forward<E1>(expr), place, places...);
  }
}

#endif


