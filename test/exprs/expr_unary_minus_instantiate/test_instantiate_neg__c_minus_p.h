#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_neg__c_minus_p()
{
  // +x1
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    po::polynomial r = po::instantiate(-(4 - p), po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      r,
      {
        { 6  , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        {-4  , { 0, 0, 0}}
      }),
      r);
  }

  PO_LINE;
}
