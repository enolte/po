#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_pos_p__plus__c()
{
  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(+p + -4, po::rank<1>{});

    assert(compare::unordered_equal_terms(
      r,
      {
        {2, {0}}
      }));
  }

  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial r = po::instantiate(+p + -4, po::rank<2>{});

    assert(compare::unordered_equal_terms(
      r,
      {
        { 6, {0, 2}},
        { 3, {1, 1}},
        {-4, {0, 0}}
      }));
  }

  PO_LINE;
}


