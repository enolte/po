#ifndef PO_STORAGE_TRIE_TERM_H
#define PO_STORAGE_TRIE_TERM_H

namespace po
{
  inline namespace trie_model
  {
    // TODO Test
    static auto find_term(const storage& terms, const po::exponents& exponents)
    {
      for(auto i{terms.monomials().cbegin()}; i != terms.monomials().cend(); ++i)
        if((i->exponents == exponents).min() == true)
          return i;

      return terms.monomials().cend();
    }

#if 0
    // TODO
    static constexpr auto find_term(const storage& terms, const po::exponents& exponents)
    {
      using namespace std::ranges;
      return find_if(
        terms.monomials(),
        [&exponents](const po::monomial& m)
        {
          return (m.exponents == exponents).min() == true;
        });
    }
#endif
  }
}

#endif


