#include "../../polynomial.h"

#include <cassert>

void test_instantiate_p_plus_pos_p()
{
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};

    po::polynomial r = po::instantiate(p + +q, po::rank<3>{});

    assert(unordered_equal(
      r.terms,
      {
        { 9. , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}}
      }));
  }

  PO_LINE;
}
