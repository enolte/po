#include "../../polynomial.h"

#include <cassert>

void test_instantiate_D__p_minus_p()
{
  {
    // p - q has 4 terms, each differentiated in place.
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p - q, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {10, {4, 1}}, {6, {1, 2}}, {-4, {0, 0}}, {0, {0, 0}}
      }),
      r);
  }

  {
    // p - q has 4 terms, each differentiated in place.
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {0, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p - q, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {10, {4, 1}}, {6, {1, 2}}, {-4, {0, 0}}, {0, {0, 0}}
      }),
      r);
  }

  {
    // p - q has 3 terms, each differentiated in place.
    po::polynomial p{{2, {0, 0}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p - q, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {0, 0}}, {6, {1, 2}}, {-4, {0, 0}}
      }),
      r.terms);
  }

  {
    // p - q has 2 terms, each differentiated in place.
    po::polynomial p{{2, {0, 0}}, {3, {2, 2}}};
    po::polynomial q{p};
    po::polynomial r = po::instantiate(po::D(p - q, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {0, 0}}, {0, {1, 2}}
      }),
      r.terms);
  }

  PO_LINE;
}
