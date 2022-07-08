#ifndef PO_COMPARE_H
#define PO_COMPARE_H

#include "../../exponents.h"

#include "../errors.h"

#include <vector>
#include <algorithm>
#include <ranges>
#include <list>

constexpr double coefficient_rel_tolerance = 0x1p-50;

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

bool operator==(const po::monomial& a, const po::monomial& b)
{
  return a.coefficient == b.coefficient && equal(a.exponents, b.exponents);
}

bool near_rel(const po::monomial& a, const po::monomial& b)
{
  return
    po_test::near_rel(a.coefficient, b.coefficient, coefficient_rel_tolerance) &&
    equal(a.exponents, b.exponents);
}


namespace compare
{
  bool exponents(const po::monomial& ta, const po::monomial& tb)
  {
    return equal(ta.exponents, tb.exponents);
  }
}


template<typename T>
bool contains_unique(const T& terms, const po::exponents& exponents)
{
  int found = 0;
  for(const auto& t : terms)
    found += equal(t.exponents, exponents);

  return found == 1;
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
// PO_TRACE(" ** " << **iia);
    bool erased = false;
    for(auto iib{std::cbegin(ib)}; iib != std::cend(ib);)
    {
// PO_TRACE("  ** " << **iib);
      if(p(**iia, **iib))
      {
// PO_TRACE("   ** match");
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
// PO_TRACE(" ** " << ia.size() << ", " << ib.size());
// for(auto i : ia)
  // std::cout << *i << ", ";
// std::cout << std::endl;
// for(auto i : ib)
  // std::cout << *i << ", ";

  return ia.size() == 0 && ib.size() == 0;
}


bool equal_exponents(const std::vector<po::monomial>& a, const std::vector<po::monomial>& b)
{
  // g++ 11.2.0: ADL requires the use of `::` here.
  return ::equal(a, b, compare::exponents);
}

bool unordered_equal(const std::vector<po::monomial>& a, const std::vector<po::monomial>& b)
{
  // g++ 11.2.0: ADL requires the use of `::` here.
  return ::equal(a, b, operator==);
}

bool unordered_near_rel(const std::vector<po::monomial>& a, const std::vector<po::monomial>& b)
{
  // g++ 11.2.0: ADL requires the use of `::` here.
  return ::equal(a, b, near_rel);
}

#endif


