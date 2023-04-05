#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_c__mult__p()
{
  {
    po::polynomial r{po::rank<3>{}};
    po::polynomial p = po::instantiate(2*r, po::rank<3>{});

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {}),
      p);

    PO_LINE;
  }

  {
    po::polynomial r{0., po::rank<3>{}};
    po::polynomial p = po::instantiate(2*r, po::rank<3>{});

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {0., {0, 0, 0}}
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(4 * p, po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {24, {0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial r = po::instantiate(4.3*p, po::rank<2>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      r,
      {
        {25.8, {0, 2}},
        {12.9, {1, 1}}
      }),
      r);

    PO_LINE;
  }
}
