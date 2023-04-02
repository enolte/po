#ifndef PO_MONOMIAL_H
#define PO_MONOMIAL_H

#include "scalar.h"
#include "exponents.h"
#include "rank.h"
#include "degree.h"
#include "../utils/pow.h"
#include "../utils/nan.h"

namespace po
{
  /*
   * A polynomial type consisting of a single term.
   */
  struct monomial
  {
    scalar_type coefficient;
    po::exponents exponents;

    /*
     * Naive implementation. Evaluate this monomial. Compute the result as a `double`, then
     * return the static cast to `scalar_type`.
     */
    template<typename ...X>
    scalar_type operator()(X... x) const
    {
      if(sizeof ...(X) != rank())
        return nan;

      double acc = 1.;
      std::size_t i = 0;
      ((acc *= utils::pow(x, exponents[i++])), ... );
      return scalar_type{acc * coefficient};
    }

    /*
     * Determine whether this is a zero term.
     */
    bool is_zero() const
    {
      return coefficient == scalar_type{0};
    }

    /*
     * Determine whether this is a constant monomial.
     */
    bool is_constant() const
    {
      return exponents.size() == 0 || exponents.sum() == 0;
    }

    /*
     * Get the exponent of the ith variable in this monomial.
     */
    exponent_type operator[](std::size_t i) const
    {
      return exponents[i];
    }

    /*
     * Degree of this monomial = sum of exponents
     */
    degree_type degree() const
    {
      return exponents.size() > 0 ? degree_type(exponents.sum()) : degree_type(0);
    }

    /*
     * The rank of a monomial := the number of variables in the monomial.
     */
    rank_type rank() const
    {
      return rank_type(exponents.size());
    }
  };



}

#endif

