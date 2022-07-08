#include "../../polynomial.h"

#include <cassert>

void test_instantiate_c_minus_p()
{
  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(4 - p, po::rank<1>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {-2, {0}}
      }),
      r);
  }

  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial r = po::instantiate(4 - p, po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {-6, {0, 2}},
        {-3, {1, 1}},
        { 4, {0, 0}}
      }),
      r);
  }

  PO_LINE;
}
