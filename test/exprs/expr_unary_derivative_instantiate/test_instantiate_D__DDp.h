#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_instantiate_D__DDp()
{
  using po::D;

  {
    po::polynomial p{{0, {5, 1, 7, 4, 3}}};
    po::polynomial r = po::instantiate(D(D(D(p, 1), 1), 2), po::rank<5>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {5, 0, 6, 4, 3}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{12, {5, 1, 7, 4, 3}}};
    po::polynomial r = po::instantiate(D(D(D(p, 0), 0), 1), po::rank<5>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {12*5*4*1, {3, 0, 7, 4, 3}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{12, {5, 1, 7, 4, 3}}};
    po::polynomial r = po::instantiate(D(D(D(p, 1), 1), 2), po::rank<5>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {5, 0, 6, 4, 3}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{12, {5, 1, 7, 4, 3}}};
    po::polynomial r = po::instantiate(D(D(D(p, 2), 2), 3), po::rank<5>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {12*7*6*4, {5, 1, 5, 3, 3}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 3, 7, 4, 3}}, {3, {2, 2, 2, 2, 2}}};
    po::polynomial r = po::instantiate(D(D(D(p, 1), 0), 1), po::rank<5>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {3*5*2*2, {4, 1, 7, 4, 3}}, {2*2*1*3, {1, 0, 2, 2, 2}}
      }),
      r);

    PO_LINE;
  }

}
