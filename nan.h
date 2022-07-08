#ifndef PO_NAN_H
#define PO_NAN_H

#include <limits>
#include "default_types.h"

namespace po
{
  template<typename T = default_numeric_type>
  constexpr T nan = std::numeric_limits<T>::quiet_NaN();
}

#endif


