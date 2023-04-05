#include "../../../polynomial.h"
#include "../../macros.h"
#include <cassert>

void test_instantiate_c()
{
  {
    po::polynomial r = po::instantiate(6);

    assert(r.rank() == 0);
    assert(r.degree() == 0);
    assert(compare::equal(r.degrees(), {}));

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {6, {}},
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial r = po::instantiate(7.7, po::rank<3>{});

    assert(r.rank() == 3);
    assert(r.degree() == 0);
    assert(compare::equal(r.degrees(), {0, 0, 0}));

    assert(compare::unordered_equal_terms(
      r,
      {
        { 7.7, { 0, 0, 0}},
      }));

    PO_LINE;
  }
}
