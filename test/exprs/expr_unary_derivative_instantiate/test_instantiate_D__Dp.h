#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_instantiate_D__Dp()
{
  using po::D;

  {
    po::polynomial p{{0, {5, 1}}};
    po::polynomial r = po::instantiate(D(D(p, 1), 1), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {5, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{0, {5, 1}}};
    po::polynomial r = po::instantiate(D(D(p, 1), 1), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {5, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(D(D(p, 1), 0), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {4, 0}}, {12, {1, 1}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(D(D(p, 0), 0), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {40, {3, 1}}, {6, {0, 2}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {0, {0, 0}}};
    po::polynomial r = po::instantiate(D(D(p, 0), 1), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {4, 0}}, {12, {1, 1}}, {0, {0, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {7, {0, 0}}};
    po::polynomial r = po::instantiate(D(D(p, 0), 7), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(D(D(p, 5), 1), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0, 0}}
      }),
      r);

    PO_LINE;
  }

}
