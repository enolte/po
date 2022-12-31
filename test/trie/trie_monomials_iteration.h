#include <iostream>
#include <cassert>

#include "../../test/macros.h"
#include "../../storage/trie/trie_monomials.h"

#include "utils.h"
#include "get_test_trie_rank3.h"

using po::operator<<;


void trie_monomials_iteration_rank3();

void trie_monomials_iteration()
{
  trie_monomials_iteration_rank3();

  PO_LINE;
}

void trie_monomials_iteration_rank3()
{
  po::trie t = get_test_trie_rank3();

  int k = -1;
  auto i = t.monomials().cbegin();
  for(; i != t.monomials().cend(); ++i)
  {
    ++k;
    // std::cout << " ** monomials = " << *i << "  ,  index = " << *i.i << std::endl;
  }

  // std::cout << " ** monomials = " << *i << "  ,  index = " << *i.i << std::endl;

  assert(k == t.coefficients.size() - 1);

  k = -1;
  const auto monomials = t.monomials();
  for(const auto& exponent : monomials)
  {
    ++k;
    // std::cout << " ** [" << k << "] monomials = " << exponent << std::endl;
  }

  assert(k == t.coefficients.size() - 1);

  k = -1;
  for(const auto& exponent : t.monomials())
  {
    ++k;
    // std::cout << " ** [" << k << "] monomials = " << exponent << std::endl;
  }

  assert(k == t.coefficients.size() - 1);
}



