#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_Dp__plus__p()
{
  {
    po::polynomial p{{2, {0, 0}}, {3, {0, 0}}};
    po::polynomial q{{4, {0, 0}}, {7, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0) + q, po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {11, {0, 0}},
        { 0, {0, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0) + q, po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {4, 1}},
        { 6, {1, 2}},
        { 4, {1, 0}},
        { 1, {0, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {1, {3, 2}}};
    po::polynomial q{{4, {1, 0}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(p, 0) + q, po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {4, 1}},
        { 4, {1, 0}},
        { 6, {2, 2}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1, 6}}, {1, {3, 2, 1}}};
    po::polynomial q{{4, {1, 0, 6}}, {3, {2, 2, 8}}};
    po::polynomial r = po::instantiate(po::D(p, 1) + q);

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {2, {5, 0, 6}},
        {2, {3, 1, 1}},
        {4, {1, 0, 6}},
        {3, {2, 2, 8}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 4, 6}}, {1, {3, 2, 1}}};
    po::polynomial q{{4, {5, 3, 6}}, {3, {2, 2, 8}}};
    po::polynomial r = po::instantiate(po::D(p, 1) + q);

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {12, {5, 3, 6}},
        { 2, {3, 1, 1}},
        { 3, {2, 2, 8}}
      }),
      r);

    PO_LINE;
  }
}

