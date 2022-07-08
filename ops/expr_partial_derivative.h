#ifndef PO_EXPR_PARTIAL_DERIVATIVE_H
#define PO_EXPR_PARTIAL_DERIVATIVE_H

#include "../polynomial.h"
#include "../utils.h"

namespace po
{
  struct expr_partial_derivative
  {
    const polynomial& expr1;
    const rank_type place;

    /*
     * Naive implementation. Evaluate a partial derivative of this polynomial. Compute the result as a `double`, then
     * return the static cast to `scalar_type`.
     */
    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      if(sizeof ...(X) != expr1.rank())
        return 0./0.;

      if(place >= expr1.rank())
        return expr1(x...);

      double acc = 0.;
      for(const auto& t : expr1.terms)
        acc += eval(t, x...);

      return acc;
    }

    template<typename ...X>
    scalar_type eval(const monomial& m, X... x) const
    {
      if(sizeof ...(X) != expr1.rank())
        return 0./0.;

      if(m.exponents[place] == 0)
        return scalar_type{0};

      double acc = 1.;
      std::size_t i = 0;
      (
        (i == place
          ? acc *= utils::pow(x, m.exponents[i++] - 1)
          : acc *= utils::pow(x, m.exponents[i++])),
        ...
      );

      return scalar_type{acc * m.coefficient * m.exponents[place]};
    }

  };





  /*
   * polynomial p = ....;
   * auto z = D(p, 4) + q;
   * ...
   *
   */
  using D = expr_partial_derivative;

}

#endif


