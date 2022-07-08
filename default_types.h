#ifndef PO_DEFAULT_TYPES_H
#define PO_DEFAULT_TYPES_H

#include <cstdint>
#include <concepts>

namespace po
{
  /*
   * Specifies the representation of the scalar field
   */
  using default_numeric_type = double;
  using numeric_type = default_numeric_type;

  /*
   * The unsigned integer type used to compute and store exponents, offsets for multiindices, etc.
   */
  using default_index_data_type = std::size_t;
  using index_data_type = default_index_data_type;
}

#endif


