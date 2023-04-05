#include "../../../ops/expr_constant.h"
#include "../../errors.h"
#include <cassert>

void test_evaluate_expr_nullary_constant()
{
  {
    po::expr_constant c{4.2};
    assert(c() == 4.2);
    assert(c(7.2) == 4.2);
    assert(c(-1, 3, 4, 5.47) == 4.2);

    PO_LINE;
  }

  {
    po::expr_constant c{4.2f};
    assert(po_test::near_rel(c(), 4.2, 0x1p-23));
    assert(po_test::near_rel(c(7.2), 4.2, 0x1p-23));
    assert(po_test::near_rel(c(-1, 3, 4, 5.47), 4.2, 0x1p-23));

    PO_LINE;
  }

  {
    po::expr_constant c{13};
    assert(c() == 13);
    assert(c(7.2) == 13);
    assert(c(-1, 3, 4, 5.47) == 13);

    PO_LINE;
  }

  {
    po::expr_constant c{(short)13};
    assert(c() == 13);
    assert(c(7.2) == 13);
    assert(c(-1, 3, 4, 5.47) == 13);

    PO_LINE;
  }
}