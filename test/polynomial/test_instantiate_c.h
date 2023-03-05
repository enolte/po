#include "../../polynomial.h"

#include <cassert>

void test_instantiate_c()
{
  {
    po::polynomial r = po::instantiate(6);

    assert(r.rank() == 0);
    assert(r.degree() == 0);
    assert(equal(r.degrees(), {}));

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {6, {}},
      }),
      r);
  }

  {
    po::polynomial r = po::instantiate(7.7, po::rank<3>{});

    assert(r.rank() == 3);
    assert(r.degree() == 0);
    assert(equal(r.degrees(), {0, 0, 0}));

    assert(unordered_equal(
      r.terms,
      {
        { 7.7, { 0, 0, 0}},
      }));
  }

  PO_LINE;
}
