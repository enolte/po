#include "../../polynomial.h"

#include <cassert>

void test_instantiate_p_mult_p_mult_p()
{
  // x0 * x1
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
   {54., { 1, 11, 7}}, {-21.6,{ 4,  9, 5}}, {45.9, {11, 11, 5}}
+
   {36., { 1, 11, 8}}, {-14.4,{ 4,  9, 6}}, {30.6, {11, 11, 6}}
*/
    po::polynomial z = po::instantiate(p * (q * r), po::rank<3>{});

    PO_ASSERT(unordered_near_rel(
      z.terms,
      {
        {54.  , { 1, 11, 7}},
        {-21.6, { 4,  9, 5}},
        {-14.4, { 4,  9, 6}},
        {45.9 , {11, 11, 5}},
        {36.  , { 1, 11, 8}},
        {30.6 , {11, 11, 6}}
      }),
      z);
  }

  // x1 * x0
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};

    po::polynomial z = po::instantiate((p * q) * r, po::rank<3>{});

    PO_ASSERT(unordered_near_rel(
      z.terms,
      {
        {54.  , { 1, 11, 7}},
        {-21.6, { 4,  9, 5}},
        {-14.4, { 4,  9, 6}},
        {45.9 , {11, 11, 5}},
        {36.  , { 1, 11, 8}},
        {30.6 , {11, 11, 6}}
      }),
      z);
  }

  PO_LINE;
}
