#ifndef PO_EXPR_CONSTANT_H
#define PO_EXPR_CONSTANT_H

#include "../field.h"

namespace po
{
  struct expr_constant
  {
    const scalar_type expr1;

    template<typename Scalar = scalar_type>
      requires supported_scalar_type<Scalar>
    constexpr expr_constant(const Scalar& _c): expr1(scalar_type(_c)) {}

    constexpr expr_constant(): expr1(scalar_type(0)) {}

    constexpr scalar_type operator()(...) const
    {
      return expr1;
    }
  };

}

#endif


