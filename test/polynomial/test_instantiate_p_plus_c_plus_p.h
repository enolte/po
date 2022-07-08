#include "../../polynomial.h"

#include <cassert>

void test_instantiate_p_plus_c_plus_p()
{
  // x1 + x0
  {
    po::polynomial p{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{ 3, {3, 3, 1}}};
    po::polynomial s = po::instantiate((p + 7.1) + q, po::rank<3>{});

    PO_ASSERT(unordered_near_rel(
      s.terms,
      {
        { 6. , { 0, 5, 3}},
        { 0.6, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        { 7.1, { 0, 0, 0}}
      }),
      s);
  }

  // x0 + x1
  {
    po::polynomial p{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{ 3, {3, 3, 1}}};
    po::polynomial s = po::instantiate(p + (7.1 + q), po::rank<3>{});

    PO_ASSERT(unordered_near_rel(
      s.terms,
      {
        { 6. , { 0, 5, 3}},
        { 0.6, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        { 7.1, { 0, 0, 0}}
      }),
      s);
  }

  // LR
  {
    po::polynomial p{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{ 3, {3, 3, 1}}};
    po::polynomial s = po::instantiate(p + 7.1 + q, po::rank<3>{});

    PO_ASSERT(unordered_near_rel(
      s.terms,
      {
        { 6. , { 0, 5, 3}},
        { 0.6, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        { 7.1, { 0, 0, 0}}
      }),
      s);
  }

  PO_LINE;
}
