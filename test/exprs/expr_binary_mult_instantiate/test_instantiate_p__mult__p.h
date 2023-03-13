#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p__mult__p()
{
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};

    po::polynomial r = po::instantiate(p * q, po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      r,
      {
        {18. , { 0, 10, 6}},
        {-7.2, { 3,  8, 4}},
        {15.3, {10, 10, 4}}
      }),
      r);
  }

  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}, { 2.8, {0, 3, 2}}};

    po::polynomial r = po::instantiate(p * q, po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      r,
      {
        {18.  , { 0, 10, 6}},
        {-7.2 , { 3,  8, 4}},
        {15.3 , {10, 10, 4}},
        {16.8 , { 0,  8, 5}},
        {-6.72, { 3,  6, 3}},
        {14.28, {10,  8, 3}}
      }),
      r);
  }

  PO_LINE;
}
