#include "../../polynomial.h"

#include <cassert>

void test_instantiate_Dp()
{
  {
    po::polynomial p{{0, {5, 1}}};
    po::polynomial r = po::instantiate(po::D(p, 1), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {5, 0}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(equal(r.degrees(), {5, 0}), r.degrees());
    PO_ASSERT(r.degree() == 5, r.degree());
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(p, 1), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {2, {5, 0}}, {6, {2, 1}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(equal(r.degrees(), {5, 1}), r.degrees());
    PO_ASSERT(r.degree() == 5, r.degree());
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(p, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {10, {4, 1}}, {6, {1, 2}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(equal(r.degrees(), {4, 2}), r.degrees());
    PO_ASSERT(r.degree() == 5, r.degree());
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {0, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {10, {4, 1}}, {6, {1, 2}}, {0, {0, 0}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(equal(r.degrees(), {4, 2}), r.degrees());
    PO_ASSERT(r.degree() == 5, r.degree());
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {7, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {10, {4, 1}}, {6, {1, 2}}, {0, {0, 0}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(equal(r.degrees(), {4, 2}), r.degrees());
    PO_ASSERT(r.degree() == 5, r.degree());
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(p, 5), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {0, 0}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(equal(r.degrees(), {0, 0}), r.degrees());
    PO_ASSERT(r.degree() == 0, r.degree());
  }


  PO_LINE;
}
