#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_D__p()
{
  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = D(p, 0);
    assert(x(1, 1, 1) == 2);
  }

  {
    po::polynomial p{{2, {1, 1, 1}}};
    assert(D(p, 0)(1, 1, 1) == 2);
  }

  {
    po::polynomial p{{3, {2, 1}}};
    auto dp0 = po::D(p, 0);
    assert(dp0(3, 1.5) == 27);
  }

  {
    po::expr_partial_derivative dp0 = po::D(po::polynomial{{3, {2, 1}}}, 0);
    assert(dp0(2, 2) == 24);
  }

  {
    po::polynomial p{};
    assert(po::D(p, 4).place == 4);
  }

  {
    po::polynomial p  {{2, {1, 1, 1}}};
    assert(D(p, 0)(1, 1, 1) == 2);
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};

    assert(po::D(p, 7)(1, 3, -1.3, 2) == 0);
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp0{{2, {0, 1, 1, 1}}, {0, {0, 4, 1, 0}}};

    assert(po::D(p, 0)(1, 3, -1.3, 2) == dp0(1, 3, -1.3, 2));
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    PO_ASSERT(
      po::D(p, 2)(1, 1, 1, 1) == dp2(1, 1, 1, 1),
      po_test::errors(po::D(p, 2)(1, 1, 1, 1), dp2(1, 1, 1, 1), 0x1p-50));
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    PO_ASSERT(
      po_test::near_rel(po::D(p, 2)(1, 3, -1.3, 2), dp2(1, 3, -1.3, 2), 0x1p-51),
      po_test::errors(po::D(p, 2)(1, 3, -1.3, 2), dp2(1, 3, -1.3, 2), 0x1p-50));
  }


  PO_LINE;
}
