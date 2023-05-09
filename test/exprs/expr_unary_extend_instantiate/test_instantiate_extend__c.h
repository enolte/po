#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_extend__c()
{
  // rank 3, test 1
  {
    po::polynomial x = po::instantiate(po::extend(6.5, 3), 3);

    assert(unordered_equal_terms(
      x,
      {
        {6.5, {0, 0, 0}}
      }));

    assert(x.rank() == 3);
    assert(x.degree() == 0);
    assert(compare::equal(x.degrees(), {0, 0, 0}));

    PO_LINE;
  }

  // rank 3, test 2
  {
    po::polynomial x = po::extend(6.5, 3);

    assert(unordered_equal_terms(
      x,
      {
        {6.5, {0, 0, 0}}
      }));

    assert(x.rank() == 3);
    assert(x.degree() == 0);
    assert(compare::equal(x.degrees(), {0, 0, 0}));

    PO_LINE;
  }
}

