#include "../../polynomial.h"

#include <cassert>

void test_instantiate_DDDp()
{
  using po::D;

  {
    po::polynomial p{{0, {5, 1, 7, 4, 3}}};
    po::polynomial r = po::instantiate(D(D(D(p, 1), 1), 2), po::rank<5>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {5, 0, 6, 4, 3}}
      }),
      r);
  }

  {
    po::polynomial p{{12, {5, 1, 7, 4, 3}}};
    po::polynomial r = po::instantiate(D(D(D(p, 0), 0), 1), po::rank<5>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {12*5*4*1, {3, 0, 7, 4, 3}}
      }),
      r);
  }

  {
    po::polynomial p{{12, {5, 1, 7, 4, 3}}};
    po::polynomial r = po::instantiate(D(D(D(p, 1), 1), 2), po::rank<5>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {5, 0, 6, 4, 3}}
      }),
      r);
  }

  {
    po::polynomial p{{12, {5, 1, 7, 4, 3}}};
    po::polynomial r = po::instantiate(D(D(D(p, 2), 2), 3), po::rank<5>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {12*7*6*4, {5, 1, 5, 3, 3}}
      }),
      r);
  }

  {
    po::polynomial p{{2, {5, 3, 7, 4, 3}}, {3, {2, 2, 2, 2, 2}}};
    po::polynomial r = po::instantiate(D(D(D(p, 1), 0), 1), po::rank<5>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {3*5*2*2, {4, 1, 7, 4, 3}}, {2*2*1*3, {1, 0, 2, 2, 2}}
      }),
      r);
  }

  PO_LINE;
}
