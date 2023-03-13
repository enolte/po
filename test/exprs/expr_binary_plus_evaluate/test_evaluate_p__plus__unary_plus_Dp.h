#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_p__plus__unary_plus_Dp()
{
  {
    po::polynomial p{{1, {3}}};
    po::polynomial q{{2, {2}}};
    assert((q + +D(p, 0))(1) == 5);
  }

  {
    po::polynomial q{{2, {2}}};
    assert((q + (+D(po::polynomial{{1, {3}}}, 0)))(1) == 5);
  }

  {
    po::polynomial p{{1, {3}}};
    assert((po::polynomial{{2, {2}}} + +D(p, 0))(1) == 5);
  }

  {
    assert(
      (
        po::polynomial{{2, {2}}}
        +
        (+D(po::polynomial{{1, {3}}}, 0))
      )(1) == 5);
  }

  PO_LINE;
}