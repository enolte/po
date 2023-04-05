#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_Dp__minus__p()
{
  {
    po::polynomial p{{2, {0, 0}}, {3, {0, 0}}};
    po::polynomial q{{4, {0, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0) - q, po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {-5, {0, 0}},
        { 0, {0, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {0, 0}}, {3, {0, 0}}};
    po::polynomial q{{4, {0, 0}}, {7, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0) - q, po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {-11, {0, 0}},
        {  0, {0, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0) - q, po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {4, 1}},
        { 6, {1, 2}},
        {-4, {1, 0}},
        {-1, {0, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {1, {3, 2}}};
    po::polynomial q{{4, {1, 0}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(p, 0) - q, po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {4, 1}},
        {-4, {1, 0}},
        { 0, {2, 2}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 0, 0, 5, 1}}, {1, {5, 0, 0, 3, 2}}};
    po::polynomial q{{4, {5, 0, 0, 1, 0}}, {3, {5, 0, 0, 2, 2}}};
    po::polynomial r = po::instantiate(po::D(p, 0) - q);

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {5, 0, 0, 4, 1}},
        {-4, {5, 0, 0, 1, 0}},
        { 0, {5, 0, 0, 2, 2}}
      }),
      r);

    PO_LINE;
  }

}

