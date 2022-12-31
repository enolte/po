#ifndef PO_TRIE_CONSTANTS_H
#define PO_TRIE_CONSTANTS_H

#include "../../exponents.h"
#include "../../field.h"

#include <limits>

namespace po
{
  namespace trie_constants
  {
    enum : exponent_type { ABSENT = exponent_type(-1) };
    static constexpr scalar_type absent_value = std::numeric_limits<scalar_type>::quiet_NaN();
  }
}

#endif


