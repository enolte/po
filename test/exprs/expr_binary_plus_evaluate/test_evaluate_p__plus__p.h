#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_p__plus__p()
{
  {
    po::polynomial p{{1, {0, 1, 3}}, {3.2, {2, 0, 0}}}, q{{3, {4, 3, 1}}};

    assert((p + q)(4, 3, 2 == p(4, 3, 2) + q(4, 3, 2)));

    PO_LINE;
  }
}
