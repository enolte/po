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
#include <tuple>

namespace po_test
{
  namespace compare
  {
    using term = std::tuple<po::scalar_type, std::initializer_list<po::exponent_type>>;
    using term_list = std::initializer_list<term>;

    bool equal(const po::exponents& xa, const po::exponents& xb)
    {
      return std::ranges::equal(xa, xb);
    }

    bool equal(const po::exponents& xa, std::initializer_list<po::exponent_type>&& xb)
    {
      return std::ranges::equal(xa, xb);
    }

    bool equal_terms(const po::monomial& xa, const term& xb)
    {
      return xa.coefficient == std::get<0>(xb) && std::ranges::equal(xa.exponents, std::get<1>(xb));
    }

    bool equal_monomials(const po::monomial& a, const po::monomial& b)
    {
      return a.coefficient == b.coefficient && compare::equal(a.exponents, b.exponents);
    }


    constexpr double default_coefficient_rel_tolerance = 0x1p-50;

    using term_predicate = std::function<bool(const po::monomial&, const term&)>;

    const term_predicate near_rel(double coefficient_rel_tolerance)
    {
      return
        [coefficient_rel_tolerance](const po::monomial& a, const term& b)
          {
            return
              po_test::near_rel(a.coefficient, std::get<0>(b), coefficient_rel_tolerance) &&
              compare::equal(a.exponents, std::get<1>(b));
          };
    }

    /*
     * Unordered comparison of monomial terms
     */
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

    bool unordered_equal_terms(const po::polynomial& p, term_list&& b)
    {
      return compare::equal(p.terms, b, equal_terms);
    }

    bool unordered_near_rel_terms(
      const po::polynomial& p,
      term_list&& b,
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
    po_test::compare::equal(a.degrees(), b.degrees()) &&
    po_test::compare::unordered_equal_terms(a, b);
}

bool operator==(const po::monomial& a, const po::monomial& b)
{
  return po_test::compare::equal_monomials(a, b);
}


#endif


