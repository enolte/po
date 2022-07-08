#ifndef PO_FIND_H
#define PO_FIND_H

#include <algorithm>
#include "../monomial.h"

namespace po
{
  /*
   * Find a term with the specified multiindex components.
   * return: non-const-iterator
   */
  constexpr auto find_constant(const std::initializer_list<monomial>& terms)
  {
    using namespace std::ranges;
    return find_if(
      terms,
      [](const auto& term)
      {
        std::size_t i = 0zu;
        return all_of(term.exponents, [](exponent_type x){return x == exponent_type{0};});
      });
  }

  /*
   * Find a term with the specified multiindex components.
   * return: non-const-iterator
   */
  constexpr auto find_constant(std::vector<monomial>& terms)
  {
    using namespace std::ranges;
    return find_if(
      terms,
      [](const auto& term)
      {
        std::size_t i = 0zu;
        return all_of(term.exponents, [](exponent_type x){return x == exponent_type{0};});
      });
  }

  /*
   * Find a term with the specified multiindex components.
   * return: non-const-iterator
   */
  template<typename ...MI>
    requires (std::integral<MI> && ...)
  constexpr auto find(std::vector<monomial>& terms, const MI&... mi)
  {
    using namespace std::ranges;
    return find_if(
      terms,
      [mi...](const auto& term)
      {
        std::size_t i = 0zu;
        return ((term.exponents[i++] == mi) && ...);
      });
  }

  /*
   * Find a term with the specified multiindex components.
   * return const-iterator
   */
  template<typename ...MI>
    requires (std::integral<MI> && ...)
  constexpr auto find(const std::vector<monomial>& terms, const MI&... mi)
  {
    using namespace std::ranges;
    return find_if(
      terms,
      [mi...](const auto& term)
      {
        std::size_t i = 0zu;
        return ((term.exponents[i++] == mi) && ...);
      });
  }

  /*
   * Find a term with the specified multiindex
   */
  constexpr auto find(std::vector<monomial>& terms, const monomial& m)
  {
    using namespace std::ranges;
    return find_if(terms, [&m](const auto& term){ return equal(term.exponents, m.exponents); });
  }

  /*
   * Find a term with the specified multiindex
   */
  constexpr auto find(std::vector<monomial>& terms, const po::exponents& exponents)
  {
    using namespace std::ranges;
    return find_if(terms, [&exponents](const auto& term){ return equal(term.exponents, exponents); });
  }


}

#endif

