#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_p_plus_c__plus__c()
{
  // LR
  {
    po::polynomial p{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{ 3, {3, 3, 1}}};
    po::polynomial s = po::instantiate(p + 12 + 7.1, po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      s,
      {
        { 6. , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        {19.1, { 0, 0, 0}}
      }),
      s);

    PO_LINE;
  }
}
