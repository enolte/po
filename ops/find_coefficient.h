#ifndef PO_FIND_COEFFICIENT_H
#define PO_FIND_COEFFICIENT_H

#include "find.h"
#include "add_eq_init_list.h"

#include "../field.h"

namespace po
{
  template<typename ...MI>
  constexpr scalar_type find_coefficient(const std::vector<monomial>& terms, MI... mi)
  {
    if(const auto found = find(terms, mi...); found != terms.cend())
      return found->coefficient;
    else
      return scalar_type{0};
  }

  template<typename ...MI>
  constexpr scalar_type& find_coefficient(std::vector<monomial>& terms, MI... mi)
  {
    if(const auto found = find(terms, mi...); found != terms.cend())
      return found->coefficient;
    else
    {
      add_eq(terms, scalar_type{0}, {exponent_type(mi)...});
      return find(terms, mi...)->coefficient;
    }
  }
}

#endif


