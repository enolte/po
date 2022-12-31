#ifndef PO_STORAGE_TRIE_ACC_MULT_H
#define PO_STORAGE_TRIE_ACC_MULT_H


namespace po
{
  inline namespace trie_model
  {
    /*
     * Accumulate a monomial, implements multiplication.
     */
    // TODO Test
    static void accumulate_mult(storage& terms, const scalar_type& c, const po::exponents& exponents)
    {
      for(auto& v : terms.vertices)
        v.value += exponents[v.level];

      for(auto& cc : terms.coefficients)
        cc *= c;
    }
  }

}

#endif


