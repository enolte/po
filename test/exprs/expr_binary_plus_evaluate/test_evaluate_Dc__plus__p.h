#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_Dc__plus__p()
{
  {
    po::polynomial p{{1, {3, 4}}};
    assert((po::D(2.3, 0) + p)(1, 2) == p(1, 2));

    PO_LINE;
  }

  {
    assert((po::D(2.7, 0) + D(po::polynomial{{1, {3}}}, 0))(1) == 3);

    PO_LINE;
  }
}