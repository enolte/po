#ifndef PO_CHANGE_RANK_H
#define PO_CHANGE_RANK_H

#include "../types/exponents.h"
#include "../types/rank.h"

#include <algorithm>

namespace po
{
  namespace detail
  {
    /*
     * assumes: rank > p.rank()
     */
    // TODO This is very inefficient.
    void increase_rank(polynomial& p, rank_type rank)
    {
      polynomial newp = polynomial::make_zero(rank);

      exponents x(scalar_type(0), rank);

      for(auto& t : p.terms)
      // for(auto& t : terms{p})
      {
        std::copy_n(cbegin(t.exponents), p.rank(), begin(x));
        newp += {t.coefficient, x};
      }

      p = newp;
    }

    /*
     * assumes: place_to_remove < p.rank()
     */
    // TODO This is very inefficient.
    void decrease_rank(polynomial& p, rank_type place_to_remove)
    {
      polynomial newp = polynomial::make_zero(p.rank() - 1);

      exponents x(scalar_type(0), p.rank() - 1);

      for(auto& t : p.terms)
      // for(auto& t : terms{p})
      {
        std::copy_n(std::cbegin(t.exponents), place_to_remove, std::begin(x));
        std::copy_n(std::cbegin(t.exponents) + place_to_remove + 1, p.rank() - (place_to_remove + 1), std::begin(x) + place_to_remove);
        t.exponents = x;
        newp += {t.coefficient, x};
      }

      p = newp;
    }

  }
}

#endif


