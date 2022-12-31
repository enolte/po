#include "../../ostream/valarray_ostream.h"

#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_expr_integral_Dp_evaluate()
{
  // r-value derivative expression
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
//  po::polynomial dp1         {{2, {1, 0, 1, 1}}}; // D(p, 1) == dp/dx1
    po::polynomial ex_dp1_2_13 {{8, {1, 0,    1}}}; // Expected integral of D(p, 1) over [1, 3] in place 2

    const double ex = ex_dp1_2_13(3, 2, 1);
    const double ac = po::integral(D(p, 1), {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 24, ac);
  }

  // l-value reference derivative expression
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
//  po::polynomial dp1         {{2, {1, 0, 1, 1}}};
    po::polynomial ex_dp1_1_13 {{4, {1,    1, 1}}}; // Expected integral of D(p, 1) over [1, 3] in place 1

    assert(ex_dp1_1_13.rank() == 3);
    const double ex = ex_dp1_1_13(3, 2, 1);

    const auto dp1 = D(p, 1);
    const double ac = po::integral(dp1, {1, {1, 3}})(3, 2, 1);

    assert(ac == ex);
    assert(ac == 24);
  }

  // r-value derivative expression
  {
    po::polynomial p           {{    2, {1, 7, 4, 8}}};
//  po::polynomial dp1         {{   14, {1, 6, 4, 8}}}; // D(p, 1) == dp/dx1
    po::polynomial ex_dp1_2_13 {{677.6, {1, 6,    8}}}; // Expected integral of D(p, 1) over [1, 3] in place 2

    const double ex = ex_dp1_2_13(3, 2, 1);
    const double ac = po::integral(D(p, 1), {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(po_test::near_rel(ac, ex, 0x1p-51), ac);
  }


  // l-value reference derivative expression
  {
    po::polynomial p           {{    2, {1, 7, 4, 8}}};
//  po::polynomial dp1         {{   14, {1, 6, 4, 8}}}; // D(p, 1) == dp/dx1
    po::polynomial ex_dp1_2_13 {{677.6, {1, 6,    8}}}; // Expected integral of D(p, 1) over [1, 3] in place 2

    const double ex = ex_dp1_2_13(3, 2, 1);

    const auto dp1 = D(p, 1);
    const double ac = po::integral(dp1, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(po_test::near_rel(ac, ex, 0x1p-51), ac);
  }

  PO_LINE;
}
