#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_p__plus__Ip()
{
  {
    po::polynomial p{{2, {0, 0, 0}}, {3, {0, 0, 0}}};
    po::polynomial q{{4, {0, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(q + po::integral(p, {0, {-1, 2}}));

    const double result_coefficient_p = 15.; // = {2 * (2 - -1) + 3 * (3 - -1);

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {result_coefficient_p + 4, {0, 0}}, // result is applied to first match found in term storage order
        {                       1, {0, 0}}
      }),
      r);
  }

  {
    po::polynomial p{{2, {0, 0, 0}}, {3, {0, 0, 0}}};
    po::polynomial q{{1, {0, 0}}, {4, {0, 0}}};
    po::polynomial r = po::instantiate(q + po::integral(p, {0, {-1, 2}}));

    const double result_coefficient_p = 15.; // = {2 * (2 - -1) + 3 * (3 - -1);

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {result_coefficient_p + 1, {0, 0}}, // result is applied to first match found in term storage order
        {                       4, {0, 0}}
      }),
      r);
  }

  {
    po::polynomial p{{2, {0, 0, 0}}, {3, {0, 3, 1}}};
    po::polynomial q{{4, {0, 0}}, {1, {0, 4}}};
    po::polynomial r = po::instantiate(q + po::integral(p, {0, {-1, 2}}));

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {0, 0}},
        { 1, {0, 4}},
        { 9, {3, 1}},
      }),
      r);
  }

  {
    po::polynomial p{{2, {0, 0, 0}}, {3, {0, 3, 1}}};
    po::polynomial q{{1, {0, 4}}, {4, {0, 0}}};
    po::polynomial r = po::instantiate(q + po::integral(p, {0, {-1, 2}}));

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {0, 0}},
        { 1, {0, 4}},
        { 9, {3, 1}},
      }),
      r);
  }

  PO_LINE;
}

