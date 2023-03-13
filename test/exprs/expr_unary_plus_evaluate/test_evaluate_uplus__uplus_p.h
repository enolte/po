#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_uplus__uplus_p()
{
  {
    po::polynomial p{{7., {3, 2}}, {-5, {2, 1}}};
    auto expr = + +p;

    assert(expr(1, 1) == p(1, 1));
    assert((+ +p)(1, 1) == p(1, 1));
    assert((+ +p)(1.7, -0.238543873) == p(1.7, -0.238543873));
  }

  PO_LINE;
}