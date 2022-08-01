#include "../../polynomial.h"

void test_mult_eq_init_list()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};

    p *= {{3, {2, 1, 4, 2}}};

    PO_ASSERT(unordered_equal(
      p.terms,
      {
        {6, {3, 2, 5, 3}}
      }),
      p);
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};

    p *= {{3, {2, 1, 4, 2}}, {6, {2, 2, 3, 2}}};

    PO_ASSERT(unordered_equal(
      p.terms,
      {
        {6 , {3, 2, 5, 3}},
        {12, {3, 3, 4, 3}}
      }),
      p);
  }

  PO_LINE;
}
