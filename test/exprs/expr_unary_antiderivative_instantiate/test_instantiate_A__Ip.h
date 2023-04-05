#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../macros.h"
#include <cassert>

#include "../expr_unary_antiderivative_evaluate/A.h"
#include "../expr_unary_integral_evaluate/I.h"

void test_instantiate_A__Ip()
{
  // lvalue polynomial, A-place in range, I-place in range
  {
    po::polynomial p{{ 2, {1, 0}}};

    po::polynomial aip = A(I(p, {0, {-1, 3}}), 0);

    PO_ASSERT(compare::unordered_equal_terms(
      aip,
      {
        {8, {1}}
      }),
      aip);

    PO_LINE;
  }

  // lvalue polynomial, A-place in range, I-place in range, test 2
  {
    po::polynomial p{{ 2, {1, 0, 2, 1}}};

    po::polynomial aip = A(I(p, {0, {-1, 3}}), 0);

    PO_ASSERT(compare::unordered_equal_terms(
      aip,
      {
        {8, {1, 2, 1}}
      }),
      aip);

    PO_LINE;
  }

}

