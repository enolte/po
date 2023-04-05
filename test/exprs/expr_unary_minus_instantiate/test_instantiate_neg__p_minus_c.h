#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_neg__p_minus_c()
{
  // -x1
  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial r = po::instantiate(-(p-8), po::rank<2>{});

    assert(compare::unordered_equal_terms(
      r,
      {
        {-6, {0, 2}},
        {-3, {1, 1}},
        { 8, {0, 0}}
      }));

    PO_LINE;
  }

}


