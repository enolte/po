#include <iostream>
#include <cassert>

#include "../../test/macros.h"
#include "../../storage/trie/trie_monomials.h"

#include "utils.h"
#include "../../ostream/monomial_ostream.h"
#include "get_test_trie_rank3.h"

using po::operator<<;

void trie_monomials_iterator_begin_rank3();

void trie_monomials_iterator_begin()
{
  trie_monomials_iterator_begin_rank3();

  PO_LINE;
}

void trie_monomials_iterator_begin_rank3()
{
  const po::trie t = get_test_trie_rank3();
  po::trie_monomials monomials{t.depth, t.vertices, t.roots, t.coefficients};

  po::trie_monomials::iterator i = monomials.cbegin();

  PO_ASSERT(i->exponents.size() == 3, i->exponents.size());
  PO_ASSERT((i->exponents == decltype(i->exponents){3, 5, 1}).min() == true, i->exponents);
  PO_ASSERT(i->coefficient == (decltype(i->coefficient){3.51}), i->coefficient);
  PO_ASSERT(i == monomials.cbegin(), *i);
}

