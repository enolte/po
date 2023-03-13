#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_p_plus_p__plus__p()
{
  // x1 + x0
  {
    po::polynomial p{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{ 3, {0, 5, 3}}};
    po::polynomial r{{-6, {0, 5, 3}}, { 5.6, {3, 3, 1}}, {5.1, { 7, 5, 1}}};
    po::polynomial s = po::instantiate((p + q) + r, po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      s,
      {
        { 3. , { 0, 5, 3}},
        { 3.2, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        { 5.1, { 7, 5, 1}}
      }),
      s);
  }

  // LR
  {
    po::polynomial p{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{ 3, {0, 5, 3}}};
    po::polynomial r{{-6, {0, 5, 3}}, { 5.6, {3, 3, 1}}, {5.1, { 7, 5, 1}}};
    po::polynomial s = po::instantiate(p + q + r, po::rank<3>{});

    assert(compare::unordered_near_rel_terms(
      s,
      {
        { 3. , { 0, 5, 3}},
        { 3.2, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        { 5.1, { 7, 5, 1}}
      }));
  }

  PO_LINE;
}
