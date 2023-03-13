#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_c_p_x_p_minus_c_x_p_x_p__minus__c_x_p()
{
  expr_unary_plus_instantiate::test_instantiate_level_6();

  po::polynomial
    r{{4, {1, 1, 1, 1, 1}}, {5, {2, 2, 2, 2, 2}}},
    q{{7, {1, 1, 1, 1, 1}}, {9, {2, 2, 2, 2, 2}}};

  po::polynomial p = 2*(r-3)*r*r - 3.2*q;
  // po::polynomial p{};
  // p = 2*(r-3)*r*r - 3.2*q;

  PO_ASSERT(compare::unordered_near_rel_terms(
    p,
    {
      {-112  , {3,3,3,3,3}},
      { 330  , {4,4,4,4,4}},
      { 600  , {5,5,5,5,5}},
      { 250  , {6,6,6,6,6}},
      {-124.8, {2,2,2,2,2}},
      { -22.4, {1,1,1,1,1}},
    }),
    p);

  PO_LINE;
}
