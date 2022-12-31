#include "../../polynomial.h"

#include <cassert>

void test_instantiate_p_plus_Ip()
{
  {
    // TODO Verify.
    po::polynomial p{{2, {0, 0}}, {3, {0, 0}}};
    po::polynomial q{{4, {0, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(q + po::integral(p, {0, {-1, 2}}), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        { 1, {0, 0}},
        {19, {0, 0}}
      }),
      r);
  }

  {
    // TODO Verify.
    po::polynomial p{{2, {0, 0}}, {3, {0, 3}}};
    po::polynomial q{{4, {0, 0}}, {1, {0, 4}}};
    po::polynomial r = po::instantiate(q + po::integral(p, {0, {-1, 2}}), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {10, {0, 0}},
        { 1, {0, 4}},
        { 9, {3, 0}},
      }),
      r);
  }
#if 0
  // TODO
  {
    po::polynomial p{{2, {0, 0}}, {3, {0, 0}}};
    po::polynomial q{{4, {0, 0}}, {7, {0, 0}}};
    po::polynomial r = po::instantiate(q + po::integral(p, {0, {-1, 2}}), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        { 4, {0, 0}},
        { 7, {0, 0}}
      }),
      r);
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(q + po::integral(p, {0, {-1, 2}}), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {10, {4, 1}},
        { 6, {1, 2}},
        { 4, {1, 0}},
        { 1, {0, 0}}
      }),
      r);
  }

  {
    po::polynomial p{{2, {5, 1}}, {1, {3, 2}}};
    po::polynomial q{{4, {1, 0}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(q + po::integral(p, {0, {-1, 2}}), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {10, {4, 1}},
        { 4, {1, 0}},
        { 6, {2, 2}}
      }),
      r);
  }
#endif
  PO_LINE;
}

