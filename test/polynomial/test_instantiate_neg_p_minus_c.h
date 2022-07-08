#include "../../polynomial.h"

#include <cassert>

void test_instantiate_neg_p_minus_c()
{
  // x1 - x0
  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(-p-8, po::rank<1>{});

    assert(unordered_equal(
      r.terms,
      {
        {-14, {0}}
      }));
  }

  // -x1
  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial r = po::instantiate(-(p-8), po::rank<2>{});

    assert(unordered_equal(
      r.terms,
      {
        {-6, {0, 2}},
        {-3, {1, 1}},
        { 8, {0, 0}}
      }));
  }

  PO_LINE;
}


