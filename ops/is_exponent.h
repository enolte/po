#ifndef PO_IS_EXPONENT_H
#define PO_IS_EXPONENT_H

#include <concepts>

namespace po
{
  // Allow signed integral representations.
  template<typename T>
  concept is_exponent = std::integral<T>;

  template<typename T>
  concept exponent = is_exponent<T>;
}

#endif

