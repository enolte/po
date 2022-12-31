#include "../../ostream/valarray_ostream.h"

#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_expr_integral_p_minus_p_instantiate();

void test_instantiate_integral_p_minus_p()
{
  test_expr_integral_p_minus_p_instantiate();

  PO_LINE;
}


void test_expr_integral_p_minus_p_instantiate()
{
  {
    po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};
    po::polynomial q{{2, {1, 2, 1}}, {5, {1, 1, 1}}};
    po::polynomial diff = po::instantiate(p - q, po::rank<3>{});

    PO_ASSERT(unordered_equal(
      diff.terms,
      {
        {-3, {1, 1, 1}},
        {-2, {1, 2, 1}},
        { 5, {3, 2, 4}},
      }),
      diff);

    // l-value source expr
    po::polynomial x_diff_1 = instantiate(po::integral(diff, 2, {0, 2}), po::rank<2>{});

    // r-value source expr
    po::polynomial x_diff_2 = instantiate(po::integral(p - q, 2, {0, 2}), po::rank<2>{});

    assert(x_diff_1.rank() == 2);
    assert(x_diff_2.rank() == 2);

    assert(unordered_equal(x_diff_1.terms, x_diff_2.terms));
    PO_ASSERT(unordered_near_rel(
      x_diff_1.terms,
      {
        {-3 * 2    , {1, 1}},
        {-2 * 2    , {1, 2}},
        { 5 * 32./5, {3, 2}},
      }),
      x_diff_1.terms);
  }
}
