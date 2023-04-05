#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_c__plus__Dp()
{
  {
    po::polynomial p{{1, {3}}};
    assert((4 + D(p, 0))(1) == 7);

    PO_LINE;
  }

  {
    assert((4 + D(po::polynomial{{1, {3}}}, 0))(1) == 7);

    PO_LINE;
  }
}
