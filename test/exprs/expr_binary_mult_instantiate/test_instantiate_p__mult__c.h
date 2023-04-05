#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p__mult__c()
{
  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(p * 3, po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {18, {0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial r = po::instantiate(p * 3, po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {18., {0, 2}},
        { 9 , {1, 1}}
      }),
      r);

    PO_LINE;
  }
}
