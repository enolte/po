#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_assign_polynomial()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    po::polynomial q(3.1, po::rank<6>{});

    q = p;

    assert(compare::unordered_equal_terms(
      q,
      {
        {4.2, {4, 0, 7, 6, 5}},
        {5.5, {3, 1, 1, 0, 0}}
      }));

    assert(q == p);
    assert(q.rank() == 5);
    assert(q.degree() == 22);
    assert(compare::equal(q.degrees(), {4, 1, 7, 6, 5}));
  }

  PO_LINE;
}
