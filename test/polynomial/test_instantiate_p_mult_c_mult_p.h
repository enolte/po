#include "../../polynomial.h"

#include <cassert>

void test_instantiate_p_mult_c_mult_p()
{
  // x0 * x1
  {
    po::polynomial p{{6, {0}}};
    po::polynomial q{{3, {3}}};
    po::polynomial r = po::instantiate(p * (3 * q), po::rank<1>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {54, {3}}
      }),
      r);
  }

  // x0 * x1
  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial q{{3, {3, 1}}};
    po::polynomial r = po::instantiate(p * (3 * q), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {54, {3, 3}},
        {27, {4, 2}},
      }),
      r);
  }

  // x0 * x1
  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial q{{3, {3, 1}}, {2, {2, 2}}};
    po::polynomial r = po::instantiate(p * (3 * q), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {72, {3, 3}},
        {27, {4, 2}},
        {36, {2, 4}},
      }),
      r);
  }

  // x1 * x0
  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial q{{3, {3, 1}}, {2, {2, 2}}};
    po::polynomial r = po::instantiate((p * 3) * q, po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {72, {3, 3}},
        {27, {4, 2}},
        {36, {2, 4}},
      }),
      r);
  }

  // LR
  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial q{{3, {3, 1}}, {2, {2, 2}}};
    po::polynomial r = po::instantiate(p * 3 * q, po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {72, {3, 3}},
        {27, {4, 2}},
        {36, {2, 4}},
      }),
      r);
  }
  PO_LINE;
}
