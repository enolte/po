#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_assign_expr_binary_plus_level_1()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial v{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial q = po::polynomial::make_constant(po::rank<5>{}, 1.4);

    PO_ASSERT(compare::unordered_equal_terms(
      q,
      {
        {1.4, {0, 0, 0, 0, 0}}
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 0, q.degree());
    PO_ASSERT(compare::equal(q.degrees(), {0, 0, 0, 0, 0}), q.degrees());

    q = u + v;

    PO_ASSERT(compare::unordered_equal_terms(
      q,
      {
        { 4.2, {4, 0, 7, 6, 5}},
        {18.5, {3, 1, 1, 0, 0}},
        { 1.2, {2, 2, 2, 2, 0}},
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 22, q.degree());
    PO_ASSERT(compare::equal(q.degrees(), {4, 2, 7, 6, 5}), q.degrees());

    PO_LINE;
  }
}
