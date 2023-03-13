#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p__mult__p_mult_p_mult_p()
{
  // x0 * x2
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};
    po::polynomial s{{3, {0, 1, 1}}, {2, {1, 0, 2}}};

    po::polynomial z = po::instantiate(p * (q * r * s), po::rank<3>{});

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
  }

  PO_LINE;
}
