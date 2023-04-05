#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

#include "../expr_unary_antiderivative_evaluate/A.h"

void test_instantiate_A__Dp()
{
  // lvalue polynomial, A-place in range, D-place in range
  {
    po::polynomial p{{ 1, {1, 0}}};

    const po::polynomial adp = A(D(p, 0), 0);

    PO_ASSERT(compare::unordered_equal_terms(
      adp,
      {
        {1, {1, 0}}
      }),
      adp);

    PO_LINE;
  }

  // rvalue polynomial, A-place in range, D-place in range
  {
    const po::polynomial adp = A(D(po::polynomial{{ 2, {1, 0}}}, 0), 0);

    PO_ASSERT(compare::unordered_equal_terms(
      adp,
      {
        {2, {1, 0}}
      }),
      adp);

    PO_LINE;
  }

  // lvalue polynomial, A-place OOR, D-place in range
  // rank-changing operation
  {
    po::polynomial p{{ 2, {1, 0}}};

    const po::polynomial adp = A(D(p, 0), 3);

    PO_ASSERT(compare::unordered_equal_terms(
      adp,
      {
        {2, {0, 0, 0, 1}}
      }),
      adp);

    PO_LINE;
  }

  // lvalue polynomial, A-place in range, D-place OOR
  {
    po::polynomial p{{ 2, {1, 0}}};

    const po::polynomial adp = A(D(p, 3), 0);

    PO_ASSERT(compare::unordered_equal_terms(
      adp,
      {
        {0, {1, 0}}
      }),
      adp);

    PO_LINE;
  }

  // lvalue polynomial, A-place OOR , D-place OOR
  // rank-changing operation
  {
    po::polynomial p{{ 2, {1, 0}}};

    po::polynomial adp = A(D(p, 5), 4);

    PO_ASSERT(compare::unordered_equal_terms(
      adp,
      {
        {0, {0, 0, 0, 0, 1}}
      }),
      adp);

    PO_LINE;
  }
}
