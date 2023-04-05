#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_p__plus__neg_p()
{
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    po::polynomial r = po::instantiate(p + -p, po::rank<3>{});

    assert(compare::unordered_equal_terms(
      r,
      {
        {0., { 0, 5, 3}},
        {0., { 3, 3, 1}},
        {0., {10, 5, 1}}
      }));

    PO_LINE;
  }
}
