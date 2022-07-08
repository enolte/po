#include "../../polynomial.h"

#include <cassert>

void test_instantiate_c_plus_pos_p()
{
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    auto r = po::instantiate(3 + +p, po::rank<3>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        { 6. , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        { 3. , { 0, 0, 0}}
      }),
      r);
  }

  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    po::polynomial r = po::instantiate(3 + +p, po::rank<3>{});

    assert(unordered_equal(
      r.terms,
      {
        { 6. , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        { 3. , { 0, 0, 0}}
      }));
  }

  PO_LINE;
}
