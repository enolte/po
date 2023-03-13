#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_mult_eq_expr_level_3()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    p *= q - 8.2*p;

    PO_ASSERT(compare::unordered_near_rel_terms(
      p,
      {
        {  6  , {3, 2, 5, 3}},
        {  9  , {2, 5, 6, 2}},
        {  2  , {2, 1, 1, 1}},
        {-32.8, {2, 2, 2, 2}},
        {-98.4, {1, 5, 3, 1}},
        {-73.8, {0, 8, 4, 0}},
        {  3  , {1, 4, 2, 0}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 15, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3, 8, 6, 3}), p.degrees());
  }

  PO_LINE;
}