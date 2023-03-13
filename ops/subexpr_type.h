#ifndef PO_SUBEXPR_TYPE_H
#define PO_SUBEXPR_TYPE_H

#include <type_traits>

namespace po
{
  namespace detail
  {
    template<typename T>
    struct subexpr : std::add_const<T> {};

    template<typename T>
    struct subexpr<const T> { using type = std::add_const_t<T>; };

    template<typename T>
    struct subexpr<T&&> { using type = std::add_const_t<T>; };

    template<typename T>
    struct subexpr<T&> { using type = std::add_const_t<T>&; };

    template<typename T>
    struct subexpr<const T&> { using type = std::add_const_t<T>&; };

    template<typename T>
    using subexpr_type = typename subexpr<T>::type;
  }

  /*
   * All expression argument types are either const T or else a type
   * of reference to a const T.
   *
   */
  template<typename T>
  using subexpr_type = detail::subexpr_type<T>;
}


#endif


