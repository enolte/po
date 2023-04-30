#ifndef PO_EXPR_CONSTANT_H
#define PO_EXPR_CONSTANT_H

#include "is_scalar.h"

namespace po
{
  struct expr_constant
  {
    using F1 = const scalar_type;

    const scalar_type expr1{scalar_type(0)};

    template<scalar Scalar = scalar_type>
    constexpr expr_constant(Scalar _c): expr1(scalar_type(_c)) {}

    constexpr expr_constant() = default;

    scalar_type operator()(...) const
    {
      return expr1;
    }
  };

}

#endif


