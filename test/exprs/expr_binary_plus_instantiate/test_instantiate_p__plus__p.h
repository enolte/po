#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_p__plus__p()
{
  {
    po::polynomial p{{6, {0}}};
    po::polynomial q{{6, {3}}};
    po::polynomial r = po::instantiate(p + q, po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {6, {0}},
        {6, {3}}
      }),
      r);

    assert(r(7.3) == p(7.3) + q(7.3));

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 4, 1}}};
    po::polynomial q{{6, {3, 1, 1}}};
    po::polynomial r = po::instantiate(p + q, po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {6, {0, 4, 1}},
        {6, {3, 1, 1}}
      }),
      r);

    assert(r(4, 2.2, -5) == p(4, 2.2, -5) + q(4, 2.2, -5));

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 4, 1}}, {-2.3, {3, 1, 1}}};
    po::polynomial q{{6, {3, 1, 1}}};
    po::polynomial r = po::instantiate(p + q, po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {6  , {0, 4, 1}},
        {3.7, {3, 1, 1}}
      }),
      r);

    assert(r(4, 2.2, -5) == p(4, 2.2, -5) + q(4, 2.2, -5));

    PO_LINE;
  }
}



