#include "../../polynomial.h"

#include <cassert>

void test_instantiate_p_minus_p()
{
  {
    po::polynomial p{{6, {0}}};
    po::polynomial q{{6, {3}}};

    po::polynomial r = po::instantiate(p - q, po::rank<1>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {6, {0}},
        {-6, {3}}
      }),
      r);
  }

  {
    po::polynomial p{{6, {0, 4, 1}}};
    po::polynomial q{{6, {3, 1, 1}}};

    po::polynomial r = po::instantiate(p - q, po::rank<3>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {6, {0, 4, 1}},
        {-6, {3, 1, 1}}
      }),
      r);
  }

  {
    po::polynomial p{{6, {0, 4, 1}}, {-2.3, {3, 1, 1}}};
    po::polynomial q{{6, {3, 1, 1}}};

    po::polynomial r = po::instantiate(p - q, po::rank<3>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        { 6  , {0, 4, 1}},
        {-8.3, {3, 1, 1}}
      }),
      r);
  }

  {
    po::polynomial p{{6, {0, 4, 1}}, {-2.3, {3, 1, 1}}};
    po::polynomial q{{6, {3, 1, 1}}};

    po::polynomial r = po::instantiate(q - p, po::rank<3>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {-6  , {0, 4, 1}},
        { 8.3, {3, 1, 1}}
      }),
      r);
  }


  PO_LINE;
}

