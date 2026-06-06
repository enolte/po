#ifndef PO_COMPARE_H
#define PO_COMPARE_H

#include "../types/exponents.h"

#include <vector>
#include <algorithm>
#include <ranges>
#include <list>
#include <functional>
#include <concepts>
#include <tuple>
#include <cmath>
#include <sstream>
#include <iomanip>

namespace po_test
{
  namespace compare
  {
    template<typename T>
    concept numeric = std::is_arithmetic<std::remove_cvref_t<T>>::value;

    namespace detail
    {
      struct empty{};
    }

    bool equal(auto&& xa, detail::empty&&)
    {
      return std::size(xa) == 0;
    }

    bool equal(auto&& xa, std::initializer_list<numeric auto>&& xb)
    {
      return std::ranges::equal(xa, xb);
    }

    inline bool rel_near(double ac, double ex, double tol)
    {
      return std::fabs(ac - ex) <= std::fabs(ex) * tol;
    }

    inline bool abs_near(double ac, double ex, double tol)
    {
      return std::fabs(ac - ex) <= tol;
    }

    inline bool abs_near(auto&& xa, std::initializer_list<numeric auto>&& xb, double tolerance = 0x1p-52)
    {
      return std::ranges::all_of(std::views::zip(xa, xb),
        [tolerance](auto&& pair) { return abs_near(std::get<0>(pair), std::get<1>(pair), tolerance); });
    }

    inline double rel(double ac, double ex)
    {
      return std::fabs(ac - ex) / std::fabs(ex);
    }

    inline double abs(double ac, double ex)
    {
      return std::fabs(ac - ex);
    }

    inline std::string errors(double ac, double ex, double tol = 0x1p-52, unsigned int precision = 6)
    {
      using namespace compare;

      const double RE = po_test::compare::rel(ac, ex);
      const double AE = po_test::compare::abs(ac, ex);

      std::stringstream ss;
      ss << std::endl
        << std::setprecision(precision) << " ac = " << ac << " = " << std::hexfloat << ac << std::endl << std::defaultfloat
        << std::setprecision(precision) << " ex = " << ex << " = " << std::hexfloat << ex << std::endl << std::defaultfloat
        << std::setprecision(precision) << " RE = " << RE << " = " << std::hexfloat << RE << std::endl << std::defaultfloat
        << std::setprecision(precision) << " AE = " << AE << " = " << std::hexfloat << AE << std::endl << std::defaultfloat
        << std::setprecision(precision) << " tol= " << tol << " = " << std::hexfloat << tol << std::endl << std::defaultfloat;

      return ss.str();
    }

    namespace detail
    {
      using term = std::tuple<po::scalar_type, std::initializer_list<po::exponent_type>>;

      bool equal_terms(const po::monomial& xa, const term& xb)
      {
        return xa.coefficient == std::get<0>(xb) && std::ranges::equal(xa.exponents, std::get<1>(xb));
      }
      bool equal_monomials(const po::monomial& a, const po::monomial& b)
      {
        return a.coefficient == b.coefficient && std::ranges::equal(a.exponents, b.exponents);
      }

      constexpr double default_coefficient_rel_tolerance = 0x1p-50;

      using term_predicate = std::function<bool(const po::monomial&, const term&)>;

      const term_predicate rel_near(double coefficient_rel_tolerance)
      {
        return
          [coefficient_rel_tolerance](const po::monomial& a, const term& b)
            {
              return
                compare::rel_near(a.coefficient, std::get<0>(b), coefficient_rel_tolerance) &&
                std::ranges::equal(a.exponents, std::get<1>(b));
            };
      }

      /*
      * Unordered comparison of monomial terms
      */
      template<typename Ra, typename Rb, typename P>
      bool unordered_equal(const Ra& a, const Rb& b, const P& p)
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
    }

    bool unordered_equal_terms(const po::polynomial& p, const po::polynomial& q)
    {
      return detail::unordered_equal(p.terms, q.terms, detail::equal_monomials);
    }

    bool unordered_equal_terms(const po::polynomial& p, std::initializer_list<detail::term>&& b)
    {
      return detail::unordered_equal(p.terms, b, detail::equal_terms);
    }

    bool unordered_near_rel_terms(
      const po::polynomial& p,
      std::initializer_list<detail::term>&& b,
      double coefficient_rel_tolerance = detail::default_coefficient_rel_tolerance)
    {
      return detail::unordered_equal(p.terms, b, detail::rel_near(coefficient_rel_tolerance));
    }
  }
}

bool operator==(const po::polynomial& a, const po::polynomial& b)
{
  using namespace po_test;

  return
    a.rank() == b.rank() &&
    a.degree() == b.degree() &&
    std::ranges::equal(a.degrees(), b.degrees()) &&
    compare::unordered_equal_terms(a, b);
}

bool operator==(const po::monomial& a, const po::monomial& b)
{
  return po_test::compare::detail::equal_monomials(a, b);
}


#endif


