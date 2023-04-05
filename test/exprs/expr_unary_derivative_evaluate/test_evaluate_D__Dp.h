#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_D__Dp()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2 {{2, {1, 1, 0, 1}}, {6 , {0, 4, 1, 0}}};
    po::polynomial dp21{{2, {1, 0, 0, 1}}, {24, {0, 3, 1, 0}}};

    PO_ASSERT(dp21(1, 1, 1, 1) == D(D(p, 2), 1)(1, 1, 1, 1),
      po_test::errors(D(D(p, 2), 1)(1, 1, 1, 1), dp21(1, 1, 1, 1), 0x1p-52));

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2 {{2, {1, 1, 0, 1}}, {6 , {0, 4, 1, 0}}};
    po::polynomial dp21{{2, {1, 0, 0, 1}}, {24, {0, 3, 1, 0}}};

    PO_ASSERT(dp21(1, 1, 1, 1) == D(p, 2, 1)(1, 1, 1, 1),
      po_test::errors(D(p, 2, 1)(1, 1, 1, 1), dp21(1, 1, 1, 1), 0x1p-52));

    PO_LINE;
  }
}
