#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_c__plus__p_plus_p()
{
  // x0 + x1
  {
    po::polynomial p{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{ 3, {3, 3, 1}}};
    po::polynomial s = po::instantiate(7.1 + (p + q));

    PO_ASSERT(compare::unordered_near_rel_terms(
      s,
      {
        { 6. , { 0, 5, 3}},
        { 0.6, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        { 7.1, { 0, 0, 0}}
      }),
      s);

    PO_LINE;
  }
}
