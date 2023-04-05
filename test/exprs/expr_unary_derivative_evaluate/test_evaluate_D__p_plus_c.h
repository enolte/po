#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_D__p_plus_c()
{
  {
    po::polynomial p{{1, {3}}};
    assert((D(p - 7, 0))(1) == 3);

    PO_LINE;
  }

  {
    assert((D(po::polynomial{{1, {3}}} + 2, 0))(1) == 3);

    PO_LINE;
  }
}
