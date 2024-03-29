#ifndef PO_MONOMIAL_H
#define PO_MONOMIAL_H

#include "../evaluate/nargs.h"
#include "../ops/is_scalar.h"
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
    template<is_scalar ...X>
    scalar_type operator()(X... x) const
    {
      if(sizeof ...(X) != rank())
        return nan;

      return this->operator()(nargs{rank()}, x...);
    }

    /*
     * Partial evaluation. Evaluate with the first n values in x...
     * This can probably be done better.
     */
    template<is_scalar ...X>
    scalar_type operator()(nargs n, X... x) const
    {
      if((n == 0 && rank() > 0) || sizeof ...(X) < n)
        return nan;

      double acc = 1.;
      std::size_t i = 0;
      ((acc *= i < n ? utils::pow(x, exponents[i++]) : 1.), ... );
      return scalar_type{acc * coefficient};
    }

    /*
     * Partial evaluation. Evaluate with the values in x..., which are
     * designated by the given offsets / places.
     * This can be done better.
     */
    template<is_scalar ...X, typename Places>
      requires std::incrementable<decltype(std::declval<Places>().cbegin())>
    scalar_type operator()(const Places& places, X... x) const
    {
      if(places.size() != exponents.size())
        // Error condition
        return nan;

      double acc = 1.;
      std::size_t i = 0; // counts ...x
      std::size_t j = 0; // counts places

      const auto accumulate = [this, &places, &acc, &i, &j](double x)
      {
        if(j < places.size() && i == places[j])
        {
          acc *= utils::pow(x, exponents[j]);
          ++j;
        }
        ++i;
      };

      (accumulate(x), ...);

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
     * Assumes: rank > 0
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

