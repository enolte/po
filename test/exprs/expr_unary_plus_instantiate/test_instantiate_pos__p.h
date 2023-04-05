#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_pos__p()
{
  {
    po::polynomial p{{6, {0}}};

    po::polynomial r = po::instantiate(+p, po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {6, {0}},
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    po::polynomial r = po::instantiate(+p, po::rank<3>{});

    assert(compare::unordered_equal_terms(
      r,
      {
        { 6  , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}}
      }));

    PO_LINE;
  }

}
