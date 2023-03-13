#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p__mult__p_mult_p_plus_p()
{
  // x0 * x2 = x0 * (x0 * x1)
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};
    po::polynomial s{{3, {0, 1, 1}}, {2, {1, 0, 2}}};

    po::polynomial z = po::instantiate(p * (q * (r + s)), po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      z,
      {
        {54, {1, 11, 7}}, {-21.6, { 4, 9, 5}}, {45.9, {11, 11, 5}},
        {36, {1, 11, 8}}, {-14.4, { 4, 9, 6}}, {30.6, {11, 11, 6}},
        {54, {0, 11, 7}}, {-21.6, { 3, 9, 5}}, {45.9, {10, 11, 5}},
        {36, {1, 10, 8}}, {-14.4, { 4, 8, 6}}, {30.6, {11, 10, 6}}
      }),
      z);
  }

#if 0
  // TODO
  // x0 * (x1 + x0))
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};
    po::polynomial s{{3, {0, 1, 1}}, {2, {1, 0, 2}}};
/*
qr =
   TODO
*/

    po::polynomial z = po::instantiate(p * ((q * r) + s), po::rank<3>{});

/*
qr + s =
  TODO

p(qr + s) =
  TODO
*/

    PO_ASSERT(compare::unordered_near_rel_terms(
      z,
      {

      }),
      z);
  }
#endif

  PO_LINE;
}
