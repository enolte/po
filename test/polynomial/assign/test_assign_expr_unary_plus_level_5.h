#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_assign_expr_unary_plus_level_5()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial v{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial q(1.4, po::rank<2>{});

    q = +(u - 3*v*(-u));

    PO_ASSERT(compare::unordered_near_rel_terms(
      q,
      {
        {  4.2 , {4, 0, 7, 6, 5}},
        {214.5 , {6, 2, 2, 0, 0}},
        { 19.8 , {5, 3, 3, 2, 0}},
        { 15.12, {6, 2, 9, 8, 5}},
        {  5.5 , {3, 1, 1, 0, 0}},
        {163.8 , {7, 1, 8, 6, 5}},
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 30, q.degree());
    PO_ASSERT(compare::equal(q.degrees(), {7, 3, 9, 8, 5}), q.degrees());

    po::polynomial q2(1.4, po::rank<23>{});

    q2 = u + 3*v*u;

    PO_ASSERT(compare::unordered_equal_terms(q, q2.terms), q2);
    PO_ASSERT(q2.rank() == 5, q2.rank());
    PO_ASSERT(q2.degree() == 30, q2.degree());
    PO_ASSERT(compare::equal(q2.degrees(), {7, 3, 9, 8, 5}), q2.degrees());

  }

  PO_LINE;
}
