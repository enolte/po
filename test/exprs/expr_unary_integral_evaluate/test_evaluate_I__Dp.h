#include "../../../ostream/valarray_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_evaluate_I__Dp()
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

  {
    po::polynomial p        {{2, {1, 1, 1, 1}}};
//  po::polynomial dp1      {{2, {1, 0, 1, 1}}};
    po::polynomial dp1_1_13 {{4, {1,    1, 1}}}; // integral of D(p, 1) over [1, 3] in place 1

    const double ex = dp1_1_13(3, 2, 1);
    assert(dp1_1_13.rank() == 3);

    const auto dp1 = D(p, 1);

    const double ac = po::integral(dp1, {1, {1, 3}})(3, 2, 1);

    assert(ac == ex);
  }

  {
    po::polynomial p        {{2, {1, 1, 1, 1}}};
//  po::polynomial dp1      {{2, {1, 0, 1, 1}}};
    po::polynomial dp1_1_13 {{4, {1,    1, 1}}}; // integral of D(p, 1) over [1, 3] in place 1

    const double ex = dp1_1_13(3, 2, 1);
    assert(dp1_1_13.rank() == 3);

    const double ac = po::integral(D(p, 1), {1, {1, 3}})(3, 2, 1);

    assert(ac == ex);
  }

  // Derivative is identically zero.
  {
    po::polynomial p        {{2, {1, 1, 1, 1}}};
//  po::polynomial dp1      {{2, {1, 0, 1, 1}}};
    po::polynomial dp1_1_13 {{4, {1,    1, 1}}}; // integral of D(p, 1) over [1, 3] in place 1

    // const double ex = dp1_1_13(3, 2, 1);
    const double ex = 0;
    assert(dp1_1_13.rank() == 3);

    const double ac = po::integral(D(p, 44), {1, {1, 3}})(3, 2, 1);

    assert(ac == ex);
  }

  // Place of integration is OOR
  {
    po::polynomial     p      {{2, {1}}};
//  po::polynomial   d0p      {{2, {0}}};    // dp/dx0
//  po::polynomial a1d0p      {{2, {0, 1}}}; // antiderivative(dp0) in place 1
    po::polynomial i1d0p      {{2, {0}}};    // integral of dp0 over [1, 3] in place 1

    const double ex = i1d0p(3) * (3 - 1);

    const double ac = po::integral(D(p, 0), {1, {1, 3}})(3);

    assert(p.rank() == instantiate(po::integral(D(p, 0), {1, {1, 3}})).rank());
    assert(p.rank() == expr_rank(po::integral(D(p, 0), {1, {1, 3}})));

    PO_ASSERT(ac == ex, po_test::errors(ac, ex, 0x1p-52));
  }

  // Place of integration is OOR
  {
    po::polynomial     p    {{2, {1, 1, 1, 1}}};
//  po::polynomial   d1p    {{2, {1, 0, 1, 1}}};          // dp/dx1
//  po::polynomial a6d1p    {{2, {1, 0, 1, 1, 0, 0, 1}}}; // antiderivative(dp/dx1) in place 6
    po::polynomial i6d1p    {{4, {1, 0, 1, 1}}};          // integral of D(p, 1) over [1, 3] in place 6 (intermediate zeroes dropped)

    const double ex = i6d1p(3, 2, 1, 2.2);
    assert(i6d1p.rank() == 4);

    const double ac = po::integral(D(p, 1), {6, {1, 3}})(3, 2, 1, 2.2);

    assert(p.rank() == instantiate(po::integral(D(p, 0), {6, {1, 3}})).rank());
    assert(p.rank() == expr_rank(po::integral(D(p, 0), {6, {1, 3}})));

    PO_ASSERT(ac == ex, po_test::errors(ac, ex, 0x1p-52));
  }

  PO_LINE;
}
