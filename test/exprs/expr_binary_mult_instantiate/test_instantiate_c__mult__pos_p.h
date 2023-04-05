#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_c__mult__pos_p()
{
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    auto r = po::instantiate(3 * +p, po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      r,
      {
        {18. , { 0, 5, 3}},
        {-7.2, { 3, 3, 1}},
        {15.3, {10, 5, 1}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    po::polynomial r = po::instantiate(3 * +p, po::rank<3>{});

    assert(compare::unordered_near_rel_terms(
      r,
      {
        {18. , { 0, 5, 3}},
        {-7.2, { 3, 3, 1}},
        {15.3, {10, 5, 1}}
      }));

    PO_LINE;
  }
}
