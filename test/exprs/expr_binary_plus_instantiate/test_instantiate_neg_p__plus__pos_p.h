#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_neg_p__plus__pos_p()
{
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{3, {0, 5, 3}}};

    po::polynomial r = po::instantiate(-p + +q, po::rank<3>{});

    assert(compare::unordered_equal_terms(
      r,
      {
        {-3. , { 0, 5, 3}},
        { 2.4, { 3, 3, 1}},
        {-5.1, {10, 5, 1}}
      }));

    PO_LINE;
  }
}
