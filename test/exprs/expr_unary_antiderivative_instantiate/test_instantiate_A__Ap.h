#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../macros.h"
#include <cassert>

#include "../expr_unary_antiderivative_evaluate/A.h"

void test_instantiate_A__Ap()
{
  // lvalue polynomial, outer place in range, inner place in range
  {
    po::polynomial p{{ 2, {1, 0}}};

    po::polynomial aap = A(A(p, 0), 0);

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {1./3 , {3, 0}}
      }),
      aap);

    PO_LINE;
  }

  // lvalue polynomial, outer place in range, inner place in range, test 2
  {
    po::polynomial p{{ 2, {1, 0, 2, 1}}};

    po::polynomial aap = A(A(p, 2), 0);

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {1./3, {2, 0, 3, 1}}
      }),
      aap);

    PO_LINE;
  }

  // lvalue polynomial, outer place in range, inner OOR
  {
    po::polynomial p{{ 2, {1, 0, 2, 1}}};

    po::polynomial aap = A(A(p, 6), 0);

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {1., {2, 0, 2, 1, 0, 0, 1}}
      }),
      aap);

    PO_LINE;
  }

  // lvalue polynomial, outer place in range, inner OOR, test 2
  {
    po::polynomial p{{ 2, {1, 0, 2, 1}}};

    po::polynomial aap = A(A(p, 6), 1);

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {2, {1, 1, 2, 1, 0, 0, 1}}
      }),
      aap);

    PO_LINE;
  }
}

