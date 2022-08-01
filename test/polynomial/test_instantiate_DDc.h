#include "../../polynomial.h"

#include <cassert>

void test_instantiate_DDc()
{
  using po::D;

  {
    po::polynomial r = po::instantiate(D(D(3.2, 0), 1), po::rank<1>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {0}},
      }),
      r);
  }

  {
    po::polynomial r = po::instantiate(D(D(3.2, 7), 3), po::rank<1>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {0}},
      }),
      r);
  }

  {
    po::polynomial r = po::instantiate(D(D(3.2, 7), 0), po::rank<4>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {0, 0, 0, 0}},
      }),
      r);
  }

  {
    po::polynomial r = po::instantiate(D(D(3.2, 0), 0), po::rank<4>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {0, 0, 0, 0}},
      }),
      r);
  }

  PO_LINE;
}

