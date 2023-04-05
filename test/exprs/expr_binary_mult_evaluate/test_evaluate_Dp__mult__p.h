#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_Dp__mult__p()
{
  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = D(p, 0) * p;
    x.expr1(1, 1, 1);

    PO_LINE;
  }

  {
    po::polynomial p{};

    using po::D;
    D(p, 0) * p;

    PO_LINE;
  }

  {
    po::polynomial p{};

    using po::D;
    const auto x = D(p, 0) * p;

    PO_LINE;
  }

  {
    po::polynomial p{};

    using po::D;
    const po::expr_binary_mult x = D(p, 0) * p;
    x.expr1(9);

    PO_LINE;
  }

  {
    po::polynomial p{};

    using po::D;
    const po::expr_binary_mult x = D(p, 0) * p;

    assert(po::is_polynomial<decltype(x.expr2)>);
    assert(x.expr2.nterms() == 0);
    // x.expr2(9);

    PO_LINE;
  }

  {
    po::polynomial p{};

    using po::D;
    const po::expr_binary_mult x = D(p, 0) * p;
    // x(9);

    PO_LINE;
  }

  {
    po::polynomial p{};

    using po::D;
    const auto x = D(p, 0) * p;
    x(9);

    PO_LINE;
  }

  {
    po::polynomial p{};

    using po::D;
    (D(p, 0) * p)(3.5);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1}}};
    assert((D(p, 0) * p)(1, 1, 1) == 4);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = D(p, 0) * p;

    // PO_ASSERT(x(1, 1, 1) == (D(p, 0) * p)(1, 1, 1), x(1, 1, 1));
    PO_ASSERT(x(1, 1, 1) == 4, x(1, 1, 1));

    PO_LINE;
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    PO_ASSERT(
      (D(p, 2) * p)(1, 1.3, -0.01, 1) == dp2(1, 1.3, -0.01, 1) * p(1, 1.3, -0.01, 1),
      po_test::errors(po::D(p, 2)(1, 1, 1, 1), dp2(1, 1, 1, 1), 0x1p-50));

    PO_LINE;
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    const auto x = D(p, 2) * p;

    PO_ASSERT(
      po_test::near_rel(x(1, 1, 1, 1), p(1, 1, 1, 1) * dp2(1, 1, 1, 1), 0x1p-50),
      po_test::errors(x(1, 1, 1, 1), p(1, 1, 1, 1) * dp2(1, 1, 1, 1), 0x1p-50));

    PO_LINE;
  }
}
