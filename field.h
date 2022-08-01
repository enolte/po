#ifndef PO_SCALAR_FIELD_H
#define PO_SCALAR_FIELD_H

#include "default_types.h"
#include "ops/is_scalar.h"

namespace po
{
  template<scalar T>
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


