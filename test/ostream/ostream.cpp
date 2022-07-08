#include "test_monomial_ostream.h"
#include "test_polynomial_ostream.h"
#include "test_trie_vertex_ostream.h"

int main()
{
  test_monomial_ostream();
  test_polynomial_ostream();
  test_trie_vertex_ostream();

  return 0;
}

