#include "../../polynomial.h"

#include <cassert>

void test_instantiate_Dp_plus_p()
{
  {
    po::polynomial p{{2, {0, 0}}, {3, {0, 0}}};
    po::polynomial q{{4, {0, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0) + q, po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        { 5, {0, 0}},
        { 0, {0, 0}}
      }),
      r);
  }

  {
    po::polynomial p{{2, {0, 0}}, {3, {0, 0}}};
    po::polynomial q{{4, {0, 0}}, {7, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0) + q, po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        { 11, {0, 0}},
        {  0, {0, 0}}
      }),
      r);
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0) + q, po::rank<2>{});

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
    po::polynomial r = po::instantiate(po::D(p, 0) + q, po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {10, {4, 1}},
        { 4, {1, 0}},
        { 6, {2, 2}}
      }),
      r);
  }

  PO_LINE;
}

