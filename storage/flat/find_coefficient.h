#ifndef PO_STORAGE_FLAT_FIND_COEFFICIENT_H
#define PO_STORAGE_FLAT_FIND_COEFFICIENT_H

#include "find_term.h"

#include <concepts>

namespace po
{
  inline namespace flat_model
  {
    template<std::integral ...MI>
    static constexpr scalar_type find_coefficient(const storage& terms, MI... mi)
    {
      if(const auto found = find_term(terms, mi...); found != terms.cend())
        return found->coefficient;
      else
        return scalar_type{0};
    }

    static constexpr scalar_type find_coefficient(const storage& terms, const po::exponents& exponents)
    {
      if(const auto found = find_term(terms, exponents); found != std::cend(terms))
        return found->coefficient;
      else
        return scalar_type{0};
    }
  }
}

#endif

