#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_D__DDp()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    assert(D(D(D(p, 2), 1), 3)(4, 0, 0, 0) == 8);
    assert(D(D(D(p, 2), 1), 3)(4, 1, 0, 0.215384) == 8);

    PO_LINE;
  }

}
