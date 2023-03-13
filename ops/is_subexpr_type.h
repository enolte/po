#ifndef PO_IS_SUBEXPR_TYPE_H
#define PO_IS_SUBEXPR_TYPE_H

#include <type_traits>

namespace po
{
  namespace detail
  {
    template<typename T>
    struct is_subexpr: std::is_const<T> { };

    template<typename T>
    struct is_subexpr<const T> : std::is_const<const T> { };

    template<typename T>
    struct is_subexpr<const T&> : std::true_type { };

    template<typename T>
    struct is_subexpr<const T&&> : std::true_type { };

    template<typename T>
    static constexpr bool is_subexpr_v = is_subexpr<T>::value;
  }

  /*
   * For type T, the following types are the associated expr field types.
   *
   *  const T
   *  const T&
   *  const T&&
   *
   * Determine whether the given type T is an expr field type.
   */
  template<typename T>
  static constexpr bool is_subexpr_type = detail::is_subexpr_v<T>;

}


#endif


