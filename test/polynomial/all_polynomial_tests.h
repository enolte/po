#include <iostream>

#include "../../test/macros.h"

#include "../../polynomial.h"

#include "../../ostream/polynomial_ostream.h"
using po::operator<<;

#include "../compare.h"
using namespace po_test;

#include "test_concepts.h"

#include "test_ctors.h"

#include "test_coefficient.h"
#include "test_nterms.h"
#include "test_degree.h"
#include "test_evaluate.h"

#include "test_assignment.h"
#include "test_add_eq.h"
#include "test_sub_eq.h"
#include "test_mult_eq.h"

#include "test_constant_term.h"
#include "test_change_rank.h"

namespace po_test
{
  void all_polynomial_tests()
  {
    test_concepts();

    test_ctors();

    test_coefficient();
    test_nterms();
    test_degree();
    test_evaluate();

    test_assignment();
    test_add_eq();
    test_sub_eq();
    test_mult_eq();

    test_constant_term();
    test_change_rank();
 }
}
