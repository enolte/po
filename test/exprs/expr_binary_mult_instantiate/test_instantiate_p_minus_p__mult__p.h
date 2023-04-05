#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p_minus_p__mult__p()
{
  // x1 * x0
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};

    po::polynomial z = po::instantiate((p - q) * r);

    PO_ASSERT(compare::unordered_near_rel_terms(
      z,
      {
        { 9  , { 1, 6, 4}},
        {-7.2, { 4, 4, 2}},
        {15.3, {11, 6, 2}},
        { 6  , { 1, 6, 5}},
        {-4.8, { 4, 4, 3}},
        {10.2, {11, 6, 3}}
      }),
      z);

    PO_LINE;
  }
}
