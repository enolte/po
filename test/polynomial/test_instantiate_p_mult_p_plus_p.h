#include "../../polynomial.h"

#include <cassert>

void test_instantiate_p_mult_p_plus_p()
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

    PO_ASSERT(unordered_near_rel(
      z.terms,
      {
        {9, {1, 6, 4}}, {6, {1, 6, 5}}, {9, {0, 6, 4}}, {6, {1, 5, 5}}
      }),
      z);
  }

  // x1 * x0
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

    PO_ASSERT(unordered_near_rel(
      z.terms,
      {
        {9, {1, 6, 4}}, {6, {1, 6, 5}}, {3, {0, 1, 1}}, {2, {1, 0, 2}}
      }),
      z);
  }
}