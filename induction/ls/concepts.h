#ifndef PO_INDUCTION_CONCEPTS_H
#define PO_INDUCTION_CONCEPTS_H

#include <concepts>

namespace po
{
  template<typename M>
  concept matrix = requires(M m)
  {
    {m[0][0]} -> std::convertible_to<double>;
  };

  template<typename M>
  concept matrix_functor = std::is_invocable_r_v<double, M, std::size_t, std::size_t>;

  template<typename F>
  concept point_functor = std::is_invocable_r_v<double, F, std::size_t>;
}

#endif


