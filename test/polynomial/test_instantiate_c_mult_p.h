#include "../../polynomial.h"

#include <cassert>

void test_instantiate_c_mult_p()
{
  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(4 * p, po::rank<1>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {24, {0}}
      }),
      r);
  }

  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial r = po::instantiate(4.3*p, po::rank<2>{});

    PO_ASSERT(unordered_near_rel(
      r.terms,
      {
        {25.8, {0, 2}},
        {12.9, {1, 1}}
      }),
      r);
  }

  PO_LINE;
}
