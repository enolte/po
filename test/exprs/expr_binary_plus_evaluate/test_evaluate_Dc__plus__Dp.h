#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_Dc__plus__Dp()
{
  {
    assert((po::D(2.7, 0) + D(po::polynomial{{1, {3}}}, 0))(1) == 3);
  }

  PO_LINE;
}

