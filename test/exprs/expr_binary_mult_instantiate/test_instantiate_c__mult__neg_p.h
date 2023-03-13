#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_c__mult__neg_p()
{
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    po::polynomial r = po::instantiate(3 * -p, po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      r,
      {
        {-18. , { 0, 5, 3}},
        {  7.2, { 3, 3, 1}},
        {-15.3, {10, 5, 1}}
      }),
      r);
  }

  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {0, 0, 0}}, {5.1, {10, 5, 1}}};

    po::polynomial r = po::instantiate(3 * -p, po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      r,
      {
        {-18. , { 0, 5, 3}},
        {-15.3, {10, 5, 1}},
        {  7.2, { 0, 0, 0}}
      }),
      r);
  }

  PO_LINE;
}
