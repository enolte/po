#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

#include "../expr_unary_antiderivative_evaluate/A.h"

void test_instantiate_A__Ac()
{
  {
    const auto x = A(A(po::expr_constant{6.}, 5), 3);

    po::polynomial p = x;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {6., {0, 0, 0, 1, 0, 1}},
      }),
      p);

    PO_LINE;
  }

  {
    const auto x = A(po::expr_constant{6.}, 5, 3);

    po::polynomial p = x;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {6., {0, 0, 0, 1, 0, 1}},
      }),
      p);

    PO_LINE;
  }

  {
    const auto x = po::A(7.2, 5, 3, 6);

    po::polynomial p = x;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {7.2, {0, 0, 0, 1, 0, 1, 1}},
      }),
      p);

    PO_LINE;
  }

}
