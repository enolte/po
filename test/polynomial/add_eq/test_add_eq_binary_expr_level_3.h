#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_add_eq_binary_expr_level_3()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    p += q - 8.2*p;

    PO_ASSERT(compare::unordered_near_rel_terms(
      p,
      {
        {-14.4, {1, 1, 1, 1}},
        {-21.6, {0, 4, 2, 0}},
        {    3, {2, 1, 4, 2}},
        {    1, {1, 0, 0, 0}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {2, 4, 4, 2}), p.degrees());
  }

  PO_LINE;
}
