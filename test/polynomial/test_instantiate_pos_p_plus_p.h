#include "../../polynomial.h"

#include <cassert>

void test_instantiate_pos_p_plus_p()
{
  // x1 + x0
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};

    po::polynomial r = po::instantiate((+p) + q, po::rank<3>{});

    PO_ASSERT(unordered_near_rel(
      r.terms,
      {
        { 9  , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}}
      }),
      r);
  }

  // +x1
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};

    po::polynomial r = po::instantiate(+(p + q), po::rank<3>{});

    PO_ASSERT(unordered_near_rel(
      r.terms,
      {
        { 9  , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}}
      }),
      r);
  }

  // LR
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};

    po::polynomial r = po::instantiate(+p + q, po::rank<3>{});

    PO_ASSERT(unordered_near_rel(
      r.terms,
      {
        { 9  , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}}
      }),
      r);
  }

  PO_LINE;
}
