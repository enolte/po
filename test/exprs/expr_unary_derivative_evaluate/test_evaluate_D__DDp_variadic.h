#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_D__DDp_variadic()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    assert(D(p, 2, 1, 3)(4, 0, 0, 0) == 8);
    assert(D(p, 2, 1, 3)(4, 1, 0, 0.215384) == 8);
  }

  {
    po::polynomial p   {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};

    assert(D(p, 2, 1, 1)(-3, 5.4, 1, 1) == 72*5.4*5.4);
    assert(D(p, 2, 1, 1)(-2, 5.4, 1, 1) == 72*5.4*5.4);
    assert(D(p, 2, 1, 1)(-1, 5.4, 1, 1) == 72*5.4*5.4);
    assert(D(p, 2, 1, 1)( 0, 5.4, 1, 1) == 72*5.4*5.4);
    assert(D(p, 2, 1, 1)( 1, 5.4, 1, 1) == 72*5.4*5.4);
    assert(D(p, 2, 1, 1)( 2, 5.4, 1, 1) == 72*5.4*5.4);
    assert(D(p, 2, 1, 1)( 3, 5.4, 1, 1) == 72*5.4*5.4);
  }

  PO_LINE;
}
