#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p_mult_p__mult__p()
{
  // x1 * x0
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};

    po::polynomial z = po::instantiate((p * q) * r, po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      z,
      {
        {54.  , { 1, 11, 7}},
        {-21.6, { 4,  9, 5}},
        {-14.4, { 4,  9, 6}},
        {45.9 , {11, 11, 5}},
        {36.  , { 1, 11, 8}},
        {30.6 , {11, 11, 6}}
      }),
      z);

    PO_LINE;
  }
}
