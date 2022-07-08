#ifndef PO_SUB_EQ_H
#define PO_SUB_EQ_H

#include "find.h"
#include "../monomial.h"

namespace po
{
  /*
   * Add a monomial term with the given coefficient and exponents
   *
   */
  template<typename ... MI>
  constexpr void sub_eq(std::vector<monomial>& terms, scalar_type&& c, MI... mi)
  {
    if(const auto found = find(terms, mi...); found != terms.cend())
      found->coefficient -= c;
    else
      terms.emplace_back(std::move(-c), exponents{exponent_type(mi)...});
  }

  constexpr void sub_eq(std::vector<monomial>& terms, scalar_type&& c, po::exponents&& exponents)
  {
    if(const auto found = find(terms, exponents); found != std::cend(terms))
      found->coefficient -= c;
    else
      terms.emplace_back(std::move(-c), std::move(exponents));
  }

  constexpr void sub_eq(std::vector<monomial>& terms, scalar_type c, const po::exponents& exponents)
  {
    if(const auto found = find(terms, exponents); found != std::cend(terms))
      found->coefficient -= c;
    else
      terms.emplace_back(-c, exponents);
  }

  constexpr void sub_eq(std::vector<monomial>& terms, monomial&& m)
  {
    if(const auto found = find(terms, m); found != std::cend(terms))
      found->coefficient -= m.coefficient;
    else
      terms.emplace_back(std::move(-m.coefficient), std::move(m.exponents));
  }

  constexpr void sub_eq(std::vector<monomial>& terms, const monomial& m)
  {
    if(const auto found = find(terms, m); found != std::cend(terms))
      found->coefficient -= m.coefficient;
    else
      terms.push_back({-m.coefficient, m.exponents});
  }
}

#endif


