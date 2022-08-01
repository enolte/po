#ifndef PO_NAN_H
#define PO_NAN_H

#include <limits>
#include "field.h"

namespace po
{
  static constexpr scalar_type nan = std::numeric_limits<scalar_type>::quiet_NaN();

}

#endif


