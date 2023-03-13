#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_assign_scalar()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    p = 51.4;

    assert(compare::unordered_equal_terms(
      p,
      {
        {51.4, {}}
      }));

    assert(p.rank() == 0);
    assert(p.degree() == 0);
    assert(compare::equal(p.degrees(), {}));
  }

  PO_LINE;
}