#include "../../ostream/valarray_ostream.h"

#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_expr_integral_p_plus_p_instantiate();

void test_instantiate_integral_p_plus_p()
{
  test_expr_integral_p_plus_p_instantiate();

  PO_LINE;
}


void test_expr_integral_p_plus_p_instantiate()
{
  {
    po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};
    po::polynomial q{{2, {1, 2, 1}}, {5, {1, 1, 1}}};
    po::polynomial sum = po::instantiate(p + q, po::rank<3>{});

    PO_ASSERT(unordered_equal(
      sum.terms,
      {
        { 7, {1, 1, 1}},
        { 2, {1, 2, 1}},
        { 5, {3, 2, 4}},
      }),
      sum);

    // l-value source expr
    po::polynomial x_sum_1 = instantiate(po::integral(sum, 2, {0, 2}), po::rank<2>{});
    assert(x_sum_1.rank() == 2);

    // TODO
    // r-value source expr
    // po::polynomial x_sum_2 = instantiate(po::integral(p + q, 2, {0, 2}), po::rank<2>{});
    // assert(x_sum_2.rank() == 2);
    // assert(unordered_equal(x_sum_1.terms, x_sum_2.terms));

    PO_ASSERT(unordered_near_rel(
      x_sum_1.terms,
      {
        { 7 * 2    , {1, 1}},
        { 2 * 2    , {1, 2}},
        { 5 * 32./5, {3, 2}},
      }),
      x_sum_1.terms);
  }
}
