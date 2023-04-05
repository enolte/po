#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_c__minus__p()
{
  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(4 - p, po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {-2, {0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial r = po::instantiate(4 - p, po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {-6, {0, 2}},
        {-3, {1, 1}},
        { 4, {0, 0}}
      }),
      r);

    PO_LINE;
  }
}
