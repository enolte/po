#ifndef PO_IS_EXPR_FIELD_TYPE_H
#define PO_IS_EXPR_FIELD_TYPE_H

#include <type_traits>

namespace po
{
  namespace detail
  {
    template<typename T>
    struct is_immutable: std::is_const<T> { };

    template<typename T>
    struct is_immutable<const T> : std::is_const<const T> { };

    template<typename T>
    struct is_immutable<const T&> : std::true_type { };

    template<typename T>
    struct is_immutable<const T&&> : std::true_type { };

    template<typename T>
    static constexpr bool is_immutable_v = is_immutable<T>::value;
  }

  /*
   * For type T, the following types are the associated immutable types.
   *
   *  const T
   *  const T&
   *  const T&&
   *
   * A reference type is already const, so call this property "immutable".
   *
   * Determine whether the given type T is immutable.
   */
  template<typename T>
  static constexpr bool is_expr_field_type = detail::is_immutable_v<T>;

}


#endif


