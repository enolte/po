#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_mult_eq_expr_level_4()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= q - 3*q + 2*q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {0, {3, 2, 5, 3}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 13, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3, 2, 5, 3}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= q - 4*q + 2*q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {-6, {3, 2, 5, 3}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 13, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3, 2, 5, 3}), p.degrees());

    PO_LINE;
  }
}