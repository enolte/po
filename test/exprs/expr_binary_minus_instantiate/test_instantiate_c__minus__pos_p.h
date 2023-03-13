#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_c__minus__pos_p()
{
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    auto r = po::instantiate(3 - +p, po::rank<3>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {-6. , { 0, 5, 3}},
        { 2.4, { 3, 3, 1}},
        {-5.1, {10, 5, 1}},
        { 3. , { 0, 0, 0}}
      }),
      r);
  }

  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {0, 0, 0}}};

    po::polynomial r = po::instantiate(3 - +p, po::rank<3>{});

    PO_ASSERT(compare::unordered_near_rel_terms(
      r,
      {
        {-6. , { 0, 5, 3}},
        { 2.4, { 3, 3, 1}},
        {-2.1, { 0, 0, 0}}
      }),
      r);
  }

  PO_LINE;
}
