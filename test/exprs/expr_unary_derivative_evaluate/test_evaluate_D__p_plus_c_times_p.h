#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_D__p_plus_c_times_p()
{
  {
    po::polynomial p{{1, {3}}}, q{{2, {2}}};
    assert(D(q + 2*p, 0)(-1) == -4 + 2*3);
  }

  PO_LINE;
}

