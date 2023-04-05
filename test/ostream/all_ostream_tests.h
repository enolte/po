#include "test_exponents_ostream.h"
#include "test_monomial_ostream.h"
#include "test_polynomial_ostream.h"

#include "../../istream/polynomial_istream.h"

namespace po_test
{
  void all_ostream_tests()
  {
    test_exponents_ostream();
    test_monomial_ostream();
    test_polynomial_ostream();
  }

}
