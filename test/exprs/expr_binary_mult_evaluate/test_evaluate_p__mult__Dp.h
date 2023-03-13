#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_p__mult__Dp()
{
  {
    po::polynomial p{{2, {4, 3}}};
    po::expr_partial_derivative dp1 = D(p, 1);

    assert( (p * dp1)(2, 1) ==  (2 * 16 * 1) * (6 * 16 * 1) );
  }

  {
    po::polynomial p  {{2, {1, 1, 1}}};

    const auto x = p * po::D(p, 2);
    x(1, 1, 1);
    PO_ASSERT(x(1, 1, 1) == 4, x(1, 1, 1));
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    const auto x = p * po::D(p, 2);

    assert(po::D(p, 2).place == 2);
    assert(po::D(p, 2)(1, 1, 1, 1) == 8);
    PO_ASSERT(
      po_test::near_rel(x(1, 1, 1, 1), 5*8, 0x1p-49),
      x(1, 1, 1, 1));
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    const auto x = p * po::D(p, 2);

    PO_ASSERT(
      po_test::near_rel(x(1, 1, 1, 1), (2 + 3)*(2 + 6), 0x1p-49),
      po_test::errors(x(1, 1, 1, 1), (2 + 3)*(2 + 6), 0x1p-49));

    PO_ASSERT(
      po_test::near_rel(x(1, 1, 1, 1), p(1, 1, 1, 1) * dp2(1, 1, 1, 1), 0x1p-50),
      po_test::errors(x(1, 1, 1, 1), p(1, 1, 1, 1) * po::D(p, 2)(1, 1, 1, 1), 0x1p-50));
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    using po::D;
    const auto x = p * D(p, 2);

    PO_ASSERT(
      x(1, 1, 1, 1) == p(1, 1, 1, 1) * dp2(1, 1, 1, 1),
      po_test::errors(x(1, 1, 1, 1), p(1, 1, 1, 1) * dp2(1, 1, 1, 1), 0x1p-50));
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    using po::D;

    PO_ASSERT(
      (p * D(p, 2))(1, 1, 1, 1) == p(1, 1, 1, 1) * dp2(1, 1, 1, 1),
      po_test::errors((p * D(p, 2))(1, 1, 1, 1), p(1, 1, 1, 1) * dp2(1, 1, 1, 1), 0x1p-50));
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    using po::D;

    PO_ASSERT(
      (p * D(p, 2))(1, 1.3, -0.01, 1) == p(1, 1.3, -0.01, 1) * dp2(1, 1.3, -0.01, 1),
      po_test::errors((p * D(p, 2))(1, 1.3, -0.01, 1), p(1, 1.3, -0.01, 1) * dp2(1, 1.3, -0.01, 1), 0x1p-50));
  }

  PO_LINE;
}