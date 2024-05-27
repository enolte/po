#include <iostream>

#include "../macros.h"
#include "../../polynomial.h"

#include "../../ostream/polynomial_ostream.h"
using po::operator<<;

#include "../compare.h"
using namespace po_test;

#include "test_expr_rank.h"

#include "test_expr_subexpressions.h"
#include "test_expr_evaluate.h"
#include "test_expr_instantiate.h"
#include "test_instance_counts.h"

namespace po_test
{
  void all_expr_tests()
  {
    test_expr_rank();

    test_expr_subexpressions();
    test_expr_evaluate();
    test_expr_instantiate();
    test_instance_counts();
  }

}


