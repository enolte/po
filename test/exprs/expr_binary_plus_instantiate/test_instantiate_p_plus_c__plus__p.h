#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p_plus_c__plus__p()
{
  // x1 + x0
  {
    po::polynomial p{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{ 3, {3, 3, 1}}};
    po::polynomial s = po::instantiate((p + 7.1) + q, po::rank<3>{});

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

  // LR
  {
    po::polynomial p{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{ 3, {3, 3, 1}}};
    po::polynomial s = po::instantiate(p + 7.1 + q, po::rank<3>{});

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
