#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p__mult__c_mult_p()
{
  // x0 * x1
  {
    po::polynomial p{{6, {0}}};
    po::polynomial q{{3, {3}}};
    po::polynomial r = po::instantiate(p * (3 * q), po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
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

    PO_ASSERT(compare::unordered_equal_terms(
      r,
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

    PO_ASSERT(compare::unordered_equal_terms(
      r,
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

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {72, {3, 3}},
        {27, {4, 2}},
        {36, {2, 4}},
      }),
      r);
  }

  PO_LINE;
}
