#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_assign_expr_binary_plus_level_3()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial v{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial q(1.4, po::rank<5>{});

    PO_ASSERT(compare::unordered_equal_terms(
      q,
      {
        {1.4, {0, 0, 0, 0, 0}}
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 0, q.degree());
    PO_ASSERT(compare::equal(q.degrees(), {0, 0, 0, 0, 0}), q.degrees());

    q = u + v*(q-v);

    PO_ASSERT(compare::unordered_equal_terms(
      q,
      {
        {   4.2 , {4,0,7,6,5}},
        {  23.7 , {3,1,1,0,0}},
        {   1.68, {2,2,2,2,0}},
        {  -1.44, {4,4,4,4,0}},
        { -31.2 , {5,3,3,2,0}},
        {-169   , {6,2,2,0,0}},
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 22, q.degree());
    PO_ASSERT(compare::equal(q.degrees(), {6, 4, 7, 6, 5}), q.degrees());
  }

  PO_LINE;
}