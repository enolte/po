#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p_mult_p__plus__p()
{
  // x1 + x0
  {
    po::polynomial q{{3, {0, 5, 3}}};
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};
    po::polynomial s{{3, {0, 1, 1}}, {2, {1, 0, 2}}};

/*
qr=
  {3, {0, 5, 3}}
*
  {3, {1, 1, 1}}, {2, {1, 1, 2}}
=
  {9, {1, 6, 4}}, {6, {1, 6, 5}}

qr+s =
=
  {9, {1, 6, 4}}, {6, {1, 6, 5}}, {3, {0, 1, 1}}, {2, {1, 0, 2}}

*/

    po::polynomial z = po::instantiate((q * r) + s, po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      z,
      {
        {9, {1, 6, 4}}, {6, {1, 6, 5}}, {3, {0, 1, 1}}, {2, {1, 0, 2}}
      }),
      z);
  }
}