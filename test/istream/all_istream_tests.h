#include "test_exponents_istream.h"
#include "test_monomial_istream.h"
#include "test_polynomial_istream.h"

#include "../../ostream/polynomial_ostream.h"

namespace po_test
{
  void all_istream_tests()
  {
    test_exponents_istream();
    test_monomial_istream();
    test_polynomial_istream();
  }

}


