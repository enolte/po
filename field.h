#ifndef PO_SCALAR_FIELD_H
#define PO_SCALAR_FIELD_H

#include "default_types.h"

#include <concepts>
#include <type_traits>

namespace po
{
  template<typename T, typename S>
  concept is = std::same_as<std::remove_cvref_t<T>, std::remove_cvref_t<S>>;

  template<typename T>
  concept supported_scalar_type =
    !is<T, void> &&
    !is<T, char> &&
    !is<T, unsigned char> &&
    !is<T, wchar_t> &&
    !is<T, std::make_unsigned<wchar_t>::type> &&
    !std::is_array_v<std::remove_cvref_t<T>> &&
    !std::is_pointer_v<std::remove_cvref_t<T>> &&
    (std::floating_point<std::remove_cvref_t<T>> || std::integral<std::remove_cvref_t<T>>);


  template<typename T>
  concept is_scalar = supported_scalar_type<T>;

  template<supported_scalar_type T>
  struct scalar_field
  {
    using type = T;

    /*
     * Use floating-point to represent an infinite field.
     * Use fixed-point to represent a finite field.
     */
    static constexpr bool is_finite = !std::floating_point<T>;
  };

  using default_scalar_type = scalar_field<default_numeric_type>::type;

  using scalar_type = scalar_field<numeric_type>::type;


}

#endif


