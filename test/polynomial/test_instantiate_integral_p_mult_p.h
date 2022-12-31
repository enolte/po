#include "../../ostream/valarray_ostream.h"

#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_expr_integral_p_mult_p_instantiate();

void test_instantiate_integral_p_mult_p()
{
  test_expr_integral_p_mult_p_instantiate();

  PO_LINE;
}


void test_expr_integral_p_mult_p_instantiate()
{
  {
    po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};

    po::polynomial p_sq = po::instantiate(p*p, po::rank<3>{});

    PO_ASSERT(unordered_equal(
      p_sq.terms,
      {
        { 4, {2, 2, 2}},
        {20, {4, 3, 5}},
        {25, {6, 4, 8}},
      }),
      p_sq);

    po::polynomial x_p_sq_1 = instantiate(po::integral(p_sq, 2, {0, 2}), po::rank<2>{});
    // PO_TRACE("x_p_sq_1 = " << x_p_sq_1);

    po::polynomial x_p_sq_2 = instantiate(po::integral(p*p , 2, {0, 2}), po::rank<2>{});
    // PO_TRACE("x_p_sq_2 = " << x_p_sq_2);

    assert(x_p_sq_1.rank() == 2);
    assert(x_p_sq_2.rank() == 2);

    assert(unordered_equal(x_p_sq_1.terms, x_p_sq_2.terms));
    PO_ASSERT(unordered_near_rel(
      x_p_sq_1.terms,
      {
        { 4 *   8./3, {2, 2}},
        {20 *  64./6, {4, 3}},
        {25 * 512./9, {6, 4}},
      }),
      x_p_sq_1.terms);
  }
}
