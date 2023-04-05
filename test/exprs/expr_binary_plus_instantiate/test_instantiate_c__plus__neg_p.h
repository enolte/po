#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_c__plus__neg_p()
{
  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    po::polynomial r = po::instantiate(3 + -p, po::rank<3>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {-6. , { 0, 5, 3}},
        { 2.4, { 3, 3, 1}},
        {-5.1, {10, 5, 1}},
        {3., { 0, 0, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {0, 0, 0}}, {5.1, {10, 5, 1}}};

    po::polynomial r = po::instantiate(3 + -p, po::rank<3>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {-6. , { 0, 5, 3}},
        {-5.1, {10, 5, 1}},
        { 5.4, { 0, 0, 0}}
      }),
      r);

    PO_LINE;
  }
}
