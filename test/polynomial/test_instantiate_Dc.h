#include "../../polynomial.h"

#include <cassert>

void test_instantiate_Dc()
{
#if 0
  // TODO
  {
    po::polynomial r = po::instantiate(po::D(3.2, 0));

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {}},
      }),
      r);
  }
#endif
  {
    po::polynomial r = po::instantiate(po::D(3.2, 0), po::rank<1>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {0}},
      }),
      r);
  }

  {
    po::polynomial r = po::instantiate(po::D(3.2, 7), po::rank<1>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {0}},
      }),
      r);
  }

  {
    po::polynomial r = po::instantiate(po::D(3.2, 7), po::rank<4>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {0, 0, 0, 0}},
      }),
      r);
  }

  {
    po::polynomial r = po::instantiate(po::D(3.2, 0), po::rank<4>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {0, 0, 0, 0}},
      }),
      r);
  }

  PO_LINE;
}

