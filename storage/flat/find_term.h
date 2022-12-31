#ifndef PO_STORAGE_FLAT_FIND_TERM_H
#define PO_STORAGE_FLAT_FIND_TERM_H

#include <algorithm>
#include <concepts>

namespace po
{
  inline namespace flat_model
  {
    /*
     * Find a term with the specified multiindex components.
     * return const-iterator
     */
    template<std::integral ...MI>
    static constexpr auto find_term(const storage& terms, const MI&... mi)
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

    static constexpr auto find_term(const storage& terms, const po::exponents& exponents)
    {
      using namespace std::ranges;
      return find_if(
        terms,
        [&exponents](const po::monomial& m)
        {
          return (m.exponents.size() == 0 && exponents.size() == 0) || (m.exponents == exponents).min() == true;
        });
    }

    static constexpr auto find_term(storage& terms, const po::exponents& exponents)
    {
      using namespace std::ranges;
      return find_if(
        terms,
        [&exponents](const po::monomial& m)
        {
          return (m.exponents.size() == 0 && exponents.size() == 0) || (m.exponents == exponents).min() == true;
        });
    }
  }
}

#endif

