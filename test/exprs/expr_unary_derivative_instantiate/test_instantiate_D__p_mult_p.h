#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_instantiate_D__p_mult_p()
{
  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p * q, 0), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {48, {5, 1}},
        {10, {4, 1}},
        {36, {2, 2}},
        { 6, {1, 2}},
      }),
      r);

    PO_LINE;
  }

  {
    // Zero terms are preserved
    // See test_instantiate_Dp_mult_p__plus__p_mult_Dp.h for product rule equivalence for this test case.
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {10, {0, 0}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p * q, 0), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {48, {5, 1}},
        {10, {4, 1}},
        {36, {2, 2}},
        { 6, {1, 2}},
        {40, {0, 0}},
        { 0, {0, 0}},
      }),
      r);

    PO_LINE;
  }

}

