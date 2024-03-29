#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p_mult_p__mult__p_mult_p()
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
/*
pqr =
   {54., { 1, 11, 7}}, {-21.6,{ 4,  9, 5}}, {45.9, {11, 11, 5}}, {36., { 1, 11, 8}}, {-14.4,{ 4,  9, 6}}, {30.6, {11, 11, 6}}
*/
    po::polynomial s{{3, {0, 1, 1}}, {2, {1, 0, 2}}};
/*
pqrs =
   { 162. , { 1, 12,  8}},
   { -64.8, { 4, 10,  6}},
   { 137.7, {11, 12,  6}},
   { 108. , { 1, 12,  9}},
   { -43.2, { 4, 10,  7}},
   {  91.8, {11, 12,  7}}

   { 108. , { 2, 11,  9}},
   { -43.2, { 5,  9,  7}},
   { 91.8 , {12, 11,  7}},
   { 72.  , { 2, 11, 10}},
   { -28.8, { 5,  9,  8}},
   { 61.2 , {12, 11,  8}}

=
*/
    po::polynomial z = po::instantiate((p * q) * (r * s), po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      z,
      {
        { 162. , { 1, 12,  8}},
        { -64.8, { 4, 10,  6}},
        { 137.7, {11, 12,  6}},
        { 108. , { 1, 12,  9}},
        { -43.2, { 4, 10,  7}},
        {  91.8, {11, 12,  7}},

        { 108. , { 2, 11,  9}},
        { -43.2, { 5,  9,  7}},
        { 91.8 , {12, 11,  7}},
        { 72.  , { 2, 11, 10}},
        { -28.8, { 5,  9,  8}},
        { 61.2 , {12, 11,  8}}
      }),
      z);

    PO_LINE;
  }
}
