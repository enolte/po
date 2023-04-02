#ifndef PO_COMPARE_H
#define PO_COMPARE_H

#include "../types/exponents.h"

#include "errors.h"

#include <vector>
#include <algorithm>
#include <ranges>
#include <list>
#include <functional>
#include <concepts>

namespace po_test
{
  namespace compare
  {
    bool equal(const po::exponents& xa, const po::exponents& xb)
    {
      return std::ranges::equal(xa, xb);
    }

    bool equal(const po::exponents& xa, std::initializer_list<po::exponent_type>&& xb)
    {
      return std::ranges::equal(xa, xb);
    }

    bool equal_monomials(const po::monomial& a, const po::monomial& b)
    {
      return a.coefficient == b.coefficient && compare::equal(a.exponents, b.exponents);
    }

    constexpr double default_coefficient_rel_tolerance = 0x1p-50;

    using term_predicate = std::function<bool(const po::monomial&, const po::monomial&)>;

    const term_predicate near_rel(double coefficient_rel_tolerance)
    {
      return
        [coefficient_rel_tolerance](const po::monomial& a, const po::monomial& b)
          {
            return
              po_test::near_rel(a.coefficient, b.coefficient, coefficient_rel_tolerance) &&
              compare::equal(a.exponents, b.exponents);
          };
    }

    /*
     * Unordered comparison of monomial terms
     */
    // template<typename Ra, typename Rb>
    // using binary_predicate = std::is_nothrow_invocable_r<bool, const typename Ra::value_type& , const typename Rb::value_type&>;

    template<typename Ra, typename Rb, typename P>
    bool equal(const Ra& a, const Rb& b, const P& p)
    {
      if(a.size() != b.size())
        return false;

      std::list<typename Ra::const_iterator> ia;
      std::list<typename Rb::const_iterator> ib;
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

    bool unordered_equal_terms(const po::polynomial& p, const po::polynomial& q)
    {
      return compare::equal(p.terms, q.terms, equal_monomials);
    }

    bool unordered_equal_terms(const po::polynomial& p, const std::vector<po::monomial>& b)
    {
      return compare::equal(p.terms, b, equal_monomials);
    }

    bool unordered_equal_terms(const po::polynomial& p, std::initializer_list<po::monomial>&& b)
    {
      return compare::equal(p.terms, b, equal_monomials);
    }

    bool unordered_near_rel_terms(
      const po::polynomial& p,
      const std::vector<po::monomial>& b,
      double coefficient_rel_tolerance = default_coefficient_rel_tolerance)
    {
      return compare::equal(p.terms, b, near_rel(coefficient_rel_tolerance));
    }
  }
}

bool operator==(const po::polynomial& a, const po::polynomial& b)
{
  using namespace po_test;

  return
    a.rank() == b.rank() &&
    a.degree() == b.degree() &&
    compare::equal(a.degrees(), b.degrees()) &&
    compare::unordered_equal_terms(a, b.terms);
}


bool operator==(const po::monomial& a, const po::monomial& b)
{
  return po_test::compare::equal_monomials(a, b);
}


#endif


