#include "../../../ostream/valarray_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_instantiate_D__DDc()
{
  using po::D;

  {
    po::polynomial r = po::instantiate(D(D(D(3.2, 0), 1), 0));

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {}},
      }),
      r);
  }

  {
    po::polynomial r = po::instantiate(D(D(D(3.2, 0), 1), 8), po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0}},
      }),
      r);
  }

  {
    po::polynomial r = po::instantiate(D(D(D(3.2, 7), 3), 0), po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0}},
      }),
      r);
  }

  {
    po::polynomial r = po::instantiate(D(D(D(3.2, 7), 0), 4), po::rank<4>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0, 0, 0, 0}},
      }),
      r);
  }

  {
    po::polynomial r = po::instantiate(D(D(D(3.2, 0), 0), 0), po::rank<4>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0, 0, 0, 0}},
      }),
      r);
  }

  PO_LINE;
}

