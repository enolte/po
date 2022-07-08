#include "../../polynomial.h"

#include <cassert>

void test_instantiate_neg_p_mult_c()
{
  // x1 * x0
  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(-p * 0.4, po::rank<1>{});

    PO_ASSERT(unordered_near_rel(
      r.terms,
      {
        {-2.4, {0}}
      }),
      r);
  }

  // x1 * x0
  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial r = po::instantiate(-p * -1.4, po::rank<2>{});

    PO_ASSERT(unordered_near_rel(
      r.terms,
      {
        {8.4, {0, 2}},
        {4.2, {1, 1}}
      }),
      r);
  }

  // x0 * x1
  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(-(p * 0.4), po::rank<1>{});

    PO_ASSERT(unordered_near_rel(
      r.terms,
      {
        {-2.4, {0}}
      }),
      r);
  }

  PO_LINE;
}
