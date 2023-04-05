#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_instantiate_D__c()
{
  {
    po::polynomial r = po::instantiate(po::D(3.2, 0));

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {}},
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial r = po::instantiate(po::D(3.2, 0), po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0}},
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial r = po::instantiate(po::D(3.2, 7), po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0}},
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial r = po::instantiate(po::D(3.2, 7), po::rank<4>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0, 0, 0, 0}},
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial r = po::instantiate(po::D(3.2, 0), po::rank<4>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0, 0, 0, 0}},
      }),
      r);

    PO_LINE;
  }

}

