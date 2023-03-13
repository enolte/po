#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p_mult_p__mult__p_plus_p()
{
  // x1 * x1
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};
/*
pq =
   {18., { 0, 10, 6}}, {-7.2, { 3,  8, 4}}, {15.3, {10, 10, 4}}
*/
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};
    po::polynomial s{{3, {0, 1, 1}}, {2, {1, 0, 2}}};

/*
r + s =
   {{3, {1, 1, 1}}, {2, {1, 1, 2}}}, {{3, {0, 1, 1}}, {2, {1, 0, 2}}}
*/
    po::polynomial z = po::instantiate((p * q) * (r + s), po::rank<3>{});
/*
pq(r+s) =

  {18., { 0, 10, 6}}, {-7.2, { 3,  8, 4}}, {15.3, {10, 10, 4}}
*
  {{3, {1, 1, 1}}, {2, {1, 1, 2}}}, {{3, {0, 1, 1}}, {2, {1, 0, 2}}}
=

  {54, {1, 11, 7}}, {-21.6, { 4, 9, 5}}, {45.9, {11, 11, 5}},
  {36, {1, 11, 8}}, {-14.4, { 4, 9, 6}}, {30.6, {11, 11, 6}},
  {54, {0, 11, 7}}, {-21.6, { 3, 9, 5}}, {45.9, {10, 11, 5}},
  {36, {1, 10, 8}}, {-14.4, { 4, 8, 6}}, {30.6, {11, 10, 6}},

*/
    PO_ASSERT(compare::unordered_near_rel_terms(
      z,
      {
        {54, {1, 11, 7}}, {-21.6, { 4, 9, 5}}, {45.9, {11, 11, 5}},
        {36, {1, 11, 8}}, {-14.4, { 4, 9, 6}}, {30.6, {11, 11, 6}},
        {54, {0, 11, 7}}, {-21.6, { 3, 9, 5}}, {45.9, {10, 11, 5}},
        {36, {1, 10, 8}}, {-14.4, { 4, 8, 6}}, {30.6, {11, 10, 6}},
      }),
      z);
  }

  PO_LINE;
}