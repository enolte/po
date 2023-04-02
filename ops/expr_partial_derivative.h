#ifndef PO_EXPR_PARTIAL_DERIVATIVE_H
#define PO_EXPR_PARTIAL_DERIVATIVE_H

#include "../types/rank.h"

namespace po
{
  template<expression>
  struct expr_partial_derivative;
}

// Specializations of expr_partial_derivative
#include "expr_partial_derivative_constant.h"
#include "expr_partial_derivative_polynomial.h"
#include "expr_partial_derivative_binary_plus.h"
#include "expr_partial_derivative_binary_minus.h"
#include "expr_partial_derivative_binary_mult.h"
#include "expr_partial_derivative_unary_plus.h"
#include "expr_partial_derivative_unary_minus.h"
#include "expr_partial_derivative_integral.h"
#include "expr_partial_derivative2.h"

namespace po
{
  /*
   * polynomial p = ...., q = ....;
   * D(p - 5*q, 4, 1, 3);
   *
   */
  template<expression E1, typename Place0, typename ...Places>
  constexpr auto D(E1&& expr, Place0 place0, Places... places)
  {
    if constexpr(sizeof ...(places) == 0)
    {
      return expr_partial_derivative<E1>{expr, po::rank_type(place0)};
    }
    else
    {
      return D(D(std::forward<E1>(expr), po::rank_type(place0)), po::rank_type(places)...);
    }
  }

}


#endif


