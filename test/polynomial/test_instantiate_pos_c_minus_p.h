#include "../../polynomial.h"

#include <cassert>

void test_instantiate_pos_c_minus_p()
{
  // +x1
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    po::polynomial r = po::instantiate(+(4 - p), po::rank<3>{});

    PO_ASSERT(unordered_near_rel(
      r.terms,
      {
        {-6  , { 0, 5, 3}},
        { 2.4, { 3, 3, 1}},
        {-5.1, {10, 5, 1}},
        { 4  , { 0, 0, 0}}
      }),
      r);
  }

  PO_LINE;
}
