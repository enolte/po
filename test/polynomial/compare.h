#ifndef PO_COMPARE_H
#define PO_COMPARE_H

#include "../../exponents.h"

#include "../errors.h"

#include <vector>
#include <algorithm>
#include <ranges>
#include <list>

/*
 * Naive comparison operators
 */
bool operator==(const po::monomial& a, const po::monomial& b);
bool operator==(const po::polynomial& a, const po::polynomial& b);

namespace compare
{
  template<typename ...Exponents>
  bool equal(const po::exponents& xa, Exponents... xb)
  {
    if(xa.size() != sizeof ...(xb))
      return false;

    int i = -1;
    return ((xa[++i] == po::exponent_type(xb)) && ...);
  }

  bool equal(const po::exponents& xa, const po::exponents& xb)
  {
    return std::equal(std::cbegin(xa), std::cend(xa), std::cbegin(xb), std::cend(xb));
  }

  bool exponents(const po::monomial& ta, const po::monomial& tb)
  {
    return equal(ta.exponents, tb.exponents);
  }

  bool operator==(const po::monomial& a, const po::monomial& b)
  {
    return a.coefficient == b.coefficient && compare::equal(a.exponents, b.exponents);
  }

  constexpr double coefficient_rel_tolerance = 0x1p-50;

  bool near_rel(const po::monomial& a, const po::monomial& b)
  {
    return
      po_test::near_rel(a.coefficient, b.coefficient, coefficient_rel_tolerance) &&
      equal(a.exponents, b.exponents);
  }

  /*
   * Unordered comparison of monomial terms
   */
  bool equal(
    const std::vector<po::monomial>& a,
    const std::vector<po::monomial>& b,
    const std::function<bool(const po::monomial&, const po::monomial&)> p)
  {
    if(a.size() != b.size())
      return false;

    std::list<std::vector<po::monomial>::const_iterator> ia, ib;
    for(auto i : std::ranges::views::iota(0zu, a.size()))
    {
      ia.push_back(std::cbegin(a) + i);
      ib.push_back(std::cbegin(b) + i);
    }

    for(auto iia{std::cbegin(ia)}; iia != std::cend(ia);)
    {
      bool erased = false;
      for(auto iib{std::cbegin(ib)}; iib != std::cend(ib);)
      {
        if(p(**iia, **iib))
        {
          iib = ib.erase(iib);
          erased = true;
          break;
        }
        else
        {
          ++iib;
        }
      }

      if(erased)
        iia = ia.erase(iia);
      else
        ++iia;
    }

    return ia.size() == 0 && ib.size() == 0;
  }

}


template<typename T>
bool contains_unique(const T& terms, const po::exponents& exponents)
{
  int nfound = 0;
  for(const auto& t : terms)
    nfound += compare::equal(t.exponents, exponents);

  return nfound == 1;
}

bool unordered_equal(const std::vector<po::monomial>& a, const std::vector<po::monomial>& b)
{
  return compare::equal(a, b, compare::operator==);
}

bool unordered_near_rel(const std::vector<po::monomial>& a, const std::vector<po::monomial>& b)
{
  return compare::equal(a, b, compare::near_rel);
}

bool operator==(const po::monomial& a, const po::monomial& b)
{
  return compare::operator==(a, b);
}

bool operator==(const po::polynomial& a, const po::polynomial& b)
{
  return
    a.this_rank == b.this_rank &&
    a.total_degree == b.total_degree &&
    compare::equal(a.variable_degrees, b.variable_degrees) &&
    unordered_equal(a.terms, b.terms) &&
    true;
}


#endif


