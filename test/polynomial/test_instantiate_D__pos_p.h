#include "../../polynomial.h"

#include <cassert>

void test_instantiate_D__pos_p()
{
  {
    po::polynomial p{{0, {5, 1}}};
    po::polynomial r = po::instantiate(po::D(+p, 1), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {5, 0}}
      }),
      r);
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(+p, 1), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {2, {5, 0}}, {6, {2, 1}}
      }),
      r);
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(+p, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {10, {4, 1}}, {6, {1, 2}}
      }),
      r);
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {0, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(+p, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {10, {4, 1}}, {6, {1, 2}}, {0, {0, 0}}
      }),
      r);
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {7, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(+p, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {10, {4, 1}}, {6, {1, 2}}, {0, {0, 0}}
      }),
      r);
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(+p, 5), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {0, {0, 0}}
      }),
      r);
  }


  PO_LINE;
}
