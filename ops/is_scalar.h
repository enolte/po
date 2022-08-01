#ifndef PO_IS_SCALAR_H
#define PO_IS_SCALAR_H

#include <concepts>

namespace po
{
  namespace detail
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
  }

  template<typename T>
  concept is_scalar = detail::supported_scalar_type<T>;

  template<typename T>
  concept scalar = is_scalar<T>;
}

#endif

