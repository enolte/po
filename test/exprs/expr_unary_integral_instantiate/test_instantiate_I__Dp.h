#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_I__Dp()
{
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
//  po::polynomial dp1         {{2, {1, 0, 1, 1}}};
    po::polynomial ex_dp1_2_13 {{8, {1, 0,    1}}}; // Expected integral of D(p, 1) over [1, 3] in place 2

    const auto expr_dp1 = D(p, 1);

    const po::polynomial dp1_lv = instantiate(expr_dp1, po::rank<4>{});
    const po::polynomial dp1_rv = instantiate(D(p, 1), po::rank<4>{});
    PO_ASSERT(compare::unordered_equal_terms(dp1_lv, dp1_rv.terms), dp1_rv);

    const po::polynomial ac_dp1_2_13 = instantiate(integral(expr_dp1, {2, {1, 3}}), po::rank<3>{});

    PO_ASSERT(compare::unordered_equal_terms(ex_dp1_2_13, ac_dp1_2_13.terms), ac_dp1_2_13);

    PO_ASSERT(ac_dp1_2_13.rank() == 3, ac_dp1_2_13.rank());
    PO_ASSERT(ac_dp1_2_13.degree() == 2, ac_dp1_2_13.degree());
    PO_ASSERT(compare::equal(ac_dp1_2_13.degrees(), {1, 0, 1}), ac_dp1_2_13.degrees());
  }

  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
//  po::polynomial dp1         {{2, {1, 0, 1, 1}}};
    po::polynomial ex_dp1_1_13 {{4, {1,    1, 1}}}; // Expected integral of D(p, 1) over [1, 3] in place 1

    const auto expr_dp1 = D(p, 1);
    const po::polynomial dp1_lv = instantiate(expr_dp1, po::rank<4>{});
    const po::polynomial dp1_rv = instantiate(D(p, 1), po::rank<4>{});
    PO_ASSERT(compare::unordered_equal_terms(dp1_lv, dp1_rv.terms), dp1_rv);

    const po::polynomial ac_dp1_1_13 = instantiate(integral(expr_dp1, {1, {1, 3}}), po::rank<3>{});

    PO_ASSERT(compare::unordered_equal_terms(ex_dp1_1_13, ac_dp1_1_13.terms), ac_dp1_1_13);

    PO_ASSERT(ac_dp1_1_13.rank() == 3, ac_dp1_1_13.rank());
    PO_ASSERT(ac_dp1_1_13.degree() == 3, ac_dp1_1_13.degree());
    PO_ASSERT(compare::equal(ac_dp1_1_13.degrees(), {1, 1, 1}), ac_dp1_1_13.degrees());
  }

  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
//  po::polynomial dp1         {{2, {1, 0, 1, 1}}};
    po::polynomial ex_dp1_3_13 {{8, {1,    0, 1}}}; // Expected integral of D(p, 1) over [1, 3] in place 3

    const auto expr_dp1 = D(p, 1);

    const po::polynomial dp1_lv = instantiate(expr_dp1, po::rank<4>{});
    const po::polynomial dp1_rv = instantiate(D(p, 1), po::rank<4>{});
    PO_ASSERT(compare::unordered_equal_terms(dp1_lv, dp1_rv.terms), dp1_rv);

    const po::polynomial ac_dp1_3_13 = instantiate(integral(expr_dp1, {3, {1, 3}}));
    PO_ASSERT(compare::unordered_equal_terms(ex_dp1_3_13, ac_dp1_3_13.terms), ac_dp1_3_13);

    PO_ASSERT(ex_dp1_3_13.rank() == 3, ex_dp1_3_13.rank());
    PO_ASSERT(ex_dp1_3_13.degree() == 2, ex_dp1_3_13.degree());
    PO_ASSERT(compare::equal(ex_dp1_3_13.degrees(), {1, 0, 1}), ex_dp1_3_13.degrees());
  }

  PO_LINE;
}
