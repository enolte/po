#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_pos_p__minus__p()
{
  // x1 - x0
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};

    po::polynomial r = po::instantiate(+p - q, po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      r,
      {
        { 3. , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}}
      }),
      r);

    PO_LINE;
  }
}
