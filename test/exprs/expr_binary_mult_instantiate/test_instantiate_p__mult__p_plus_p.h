#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p__mult__p_plus_p()
{
  // x0 * x1
  {
    po::polynomial q{{3, {0, 5, 3}}};
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};
    po::polynomial s{{3, {0, 1, 1}}, {2, {1, 0, 2}}};

/*
r + s = {3, {1, 1, 1}}, {2, {1, 1, 2}}, {3, {0, 1, 1}}, {2, {1, 0, 2}}

q(r+s) =
  {3, {0, 5, 3}}
*
  {3, {1, 1, 1}}, {2, {1, 1, 2}}, {3, {0, 1, 1}}, {2, {1, 0, 2}}
=
  {9, {1, 6, 4}}, {6, {1, 6, 5}}, {9, {0, 6, 4}}, {6, {1, 5, 5}}

*/

    po::polynomial z = po::instantiate(q * (r + s), po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      z,
      {
        {9, {1, 6, 4}}, {6, {1, 6, 5}}, {9, {0, 6, 4}}, {6, {1, 5, 5}}
      }),
      z);

    PO_LINE;
  }

}