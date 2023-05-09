#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_mult_eq_expr_level_2()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};

    p *= 2 + 6*po::polynomial{{3, {2, 1, 4, 2}}};

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {36, {3, 2, 5, 3}},
        { 4, {1, 1, 1, 1}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 13, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3, 2, 5, 3}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= q*q*q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {54, {7, 4,13, 7}},
        {81, {6, 7,14, 6}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 33, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {7, 7,14, 7}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};

    p *= p*p + 3;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 8, {3, 3, 3, 3}},
        {54, {1, 9, 5, 1}},
        { 6, {1, 1, 1, 1}},
        { 9, {0, 4, 2, 0}},
        {27, {0,12, 6, 0}},
        {36, {2, 6, 4, 2}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 18, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3,12, 6, 3}), p.degrees());

    PO_LINE;
  }
}