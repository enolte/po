#include "../../polynomial.h"

#include <cassert>

void test_instantiate_neg_p_plus_c()
{
  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(-p + -4, po::rank<1>{});

    assert(unordered_equal(
      r.terms,
      {
        {-10, {0}}
      }));
  }

  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial r = po::instantiate(-p + -4, po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {-6, {0, 2}},
        {-3, {1, 1}},
        {-4, {0, 0}}
      }),
      r);
  }

  PO_LINE;
}


