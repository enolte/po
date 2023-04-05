#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_assign_init_list()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    p = {{0.77, {2, 2, 2, 2, 2}}, {0.1, {1, 2, 3, 4, 5}}};

    assert(compare::unordered_equal_terms(
      p,
      {
        {0.77, {2, 2, 2, 2, 2}},
        {0.1 , {1, 2, 3, 4, 5}}
      }));

    assert(p.rank() == 5);
    assert(p.degree() == 15);
    assert(compare::equal(p.degrees(), {2, 2, 3, 4, 5}));

    PO_LINE;
  }
}
