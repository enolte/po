#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_extend__p()
{
  {
    po::polynomial p{{3.2, {3, 2}}, {2.2, {2, 2}}};

    po::polynomial xp = po::instantiate(extend(p, 4, 1, 2));

    assert(xp.rank() == 4);

    PO_ASSERT(unordered_equal_terms(
      xp,
      {
        {3.2, {0, 3, 2, 0}},
        {2.2, {0, 2, 2, 0}}
      }),
      xp);

    PO_LINE;
  }

  {
    po::polynomial p{{3.2, {3, 2, 0, 4}}, {2.2, {2, 2, 8, 6}}};

    po::polynomial xp = po::instantiate(extend(p, 7, 1, 2, 4, 5));

    assert(xp.rank() == 7);

    PO_ASSERT(unordered_equal_terms(
      xp,
      {
        {3.2, {0, 3, 2, 0, 0, 4, 0}},
        {2.2, {0, 2, 2, 0, 8, 6, 0}}
      }),
      xp);

    PO_LINE;
  }

  // rank 4 -- > rank 7, change variable order.
  // TODO Disallow this.
  {
    po::polynomial p{{3.2, {3, 2, 0, 4}}, {2.2, {2, 2, 8, 6}}};

    po::polynomial xp = po::instantiate(extend(p, 7, 1, 2, 6, 5));

    assert(xp.rank() == 7);

    PO_ASSERT(unordered_equal_terms(
      xp,
      {
        {3.2, {0, 3, 2, 0, 0, 4, 0}},
        {2.2, {0, 2, 2, 0, 0, 6, 8}}
      }),
      xp);

    PO_LINE;
  }
}


