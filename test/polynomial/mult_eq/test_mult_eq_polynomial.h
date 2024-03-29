#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_mult_eq_polynomial()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};

    p *= po::polynomial{{3, {2, 1, 4, 2}}};

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {6, {3, 2, 5, 3}}
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= std::move(q);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {6, {3, 2, 5, 3}}
      }),
      p);

    // TODO A move has no effect on a polynomial in a *= expression
    PO_ASSERT(compare::unordered_equal_terms(
      q,
      {
        {3, {2, 1, 4, 2}}
      }),
      q);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {6, {3, 2, 5, 3}}
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {6, {3, 2, 5, 3}},
        {9, {2, 5, 6, 2}}
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

/*
    (2   1 1 1 1     +     3   0 4 2 0) * (3   2 1 4 2)
   = 6   3 2 5 3     +     9   2 5 6 2

    (2   1 1 1 1     +     3   0 4 2 0) * (1   1 0 0 0)
   = 2   2 1 1 1     +     3   1 4 2 0

sum: {6, {3, 2, 5, 3}}, {9, {2, 5, 6, 2}}, {2, {2, 1, 1, 1}}, {3, {1, 4, 2, 0}}
*/

    p *= q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {6, {3, 2, 5, 3}},
        {9, {2, 5, 6, 2}},
        {2, {2, 1, 1, 1}},
        {3, {1, 4, 2, 0}}
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 4, 2, 1}}, {3, {2, 5, 7, 2}}};
    po::polynomial q{{3, {2, 1, 5, 2}}, {1, {1, 0, 0, 1}}};

/*
    (2   1 4 2 1     +     3   2 5 7  2) * (3   2 1 5 2)
   = 6   3 5 7 3     +     9   4 6 12 4

    (2   1 4 2 1     +     3   2 5 7  2) * (1   1 0 0 1)
   = 2   2 4 2 2     +     3   3 5 7  3

sum= 9   3 5 7 3     +     9   4 6 12 4     +     2   2 4 2 2
   = {9, {3, 2, 7, 3}}, {9, {4, 6, 12, 4}}, {2, {2, 4, 2, 2}}
*/

    p *= q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {9, {3, 5, 7, 3}},
        {9, {4, 6, 12, 4}},
        {2, {2, 4, 2, 2}}
      }),
      p);

    PO_LINE;
  }
}