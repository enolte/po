#ifndef PO_SCALAR_TERM_MULT_EQ_H
#define PO_SCALAR_TERM_MULT_EQ_H

#include "find.h"
#include "../monomial.h"

namespace po
{
  /*
   * Multiply a single term by a scalar
   *
   */
  template<typename ... MI>
  constexpr void scalar_mult_term_eq(std::vector<monomial>& terms, double s, scalar_type c, MI... mi)
  {
    if(const auto found = find(terms, mi...); found != terms.cend())
      found->coefficient += c;
    else
      terms.emplace_back(c, exponents{exponent_type(mi)...});
  }

  constexpr void scalar_mult_term_eq(std::vector<monomial>& terms, scalar_type c, po::exponents&& exponents, double s)
  {
    if(const auto found = find(terms, exponents); found != std::cend(terms))
      found->coefficient += c;
    else
      terms.emplace_back(c, std::move(exponents));
  }

  constexpr void scalar_mult_term_eq(std::vector<monomial>& terms, scalar_type c, const po::exponents& exponents, double s)
  {
    if(const auto found = find(terms, exponents); found != std::cend(terms))
      found->coefficient += c;
    else
      terms.push_back({c, exponents});
  }

  constexpr void scalar_mult_term_eq(std::vector<monomial>& terms, monomial&& m, double s)
  {
    if(const auto found = find(terms, m); found != std::cend(terms))
      found->coefficient += m.coefficient;
    else
      terms.emplace_back(m);
  }

  constexpr void scalar_mult_term_eq(std::vector<monomial>& terms, const monomial& m, double s)
  {
    if(const auto found = find(terms, m); found != std::cend(terms))
      found->coefficient += m.coefficient;
    else
      terms.push_back(m);
  }
}

#endif


