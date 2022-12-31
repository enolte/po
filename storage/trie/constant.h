#ifndef PO_STORAGE_TRIE_CONSTANT_H
#define PO_STORAGE_TRIE_CONSTANT_H

namespace po
{
  inline namespace trie_model
  {
    // TODO Test
    static scalar_type constant(const storage& terms)
    {
      scalar_type constant{0};

      for(const auto& term : terms.monomials())
        if(term.degree() == 0)
          constant += term.coefficient;

      return constant;
    }
#if 0
    // TODO
    static constexpr scalar_type constant(const storage& terms)
    {
      scalar_type constant{0};

      std::ranges::for_each(
        terms.monomials(),
        [&constant](const auto& term)
        {
          if(term.degree() == 0)
            constant += term.coefficient;
        });

      return constant;
    }
#endif
  }

}

#endif