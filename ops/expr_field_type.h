#ifndef PO_EXPR_FIELD_TYPE_H
#define PO_EXPR_FIELD_TYPE_H

#include <type_traits>

namespace po
{
  namespace detail
  {
    template<typename T>
    struct immutable_field : std::add_const<T> {};

    template<typename T>
    struct immutable_field<const T> { using type = std::add_const_t<T>; };

    template<typename T>
    struct immutable_field<T&&> { using type = std::add_const_t<T>; };

    template<typename T>
    struct immutable_field<T&> { using type = std::add_const_t<T>&; };

    template<typename T>
    struct immutable_field<const T&> { using type = std::add_const_t<T>&; };

    template<typename T>
    using immutable_field_t = typename immutable_field<T>::type;
  }

  /*
   * All expression argument types are immutable (either const T or else a type of reference to a const T).
   *
   * A reference type is already const, so call this property "immutable".
   */
  template<typename T>
  using expr_field_type = detail::immutable_field_t<T>;
}


#endif


