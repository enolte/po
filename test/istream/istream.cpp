#include "test_exponents_istream.h"
#include "test_monomial_istream.h"
#include "test_polynomial_istream.h"

#include "../../ostream/polynomial_ostream.h"

int main()
{
  test_exponents_istream();
  test_monomial_istream();
  test_polynomial_istream();

  PO_LINE;

  return 0;
}
