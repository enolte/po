#include "../../polynomial.h"

#include <cassert>

void test_instantiate_p_mult_c()
{
  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(p * 3, po::rank<1>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {18, {0}}
      }),
      r);
  }

  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial r = po::instantiate(p * 3, po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {18., {0, 2}},
        { 9 , {1, 1}}
      }),
      r);
  }

  PO_LINE;
}
