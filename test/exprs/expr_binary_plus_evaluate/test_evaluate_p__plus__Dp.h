#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_p__plus__Dp()
{
  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = p + D(p, 0);

    PO_LINE;
  }

  {
    po::polynomial p{{1, {3}}};
    po::polynomial q{{2, {2}}};
    assert((q + D(p, 0))(1) == 5);

    PO_LINE;
  }

  {
    po::polynomial q{{2, {2}}};
    assert((q + D(po::polynomial{{1, {3}}}, 0))(1) == 5);

    PO_LINE;
  }

  {
    po::polynomial p{{1, {3}}};
    assert((po::polynomial{{2, {2}}} + D(p, 0))(1) == 5);

    PO_LINE;
  }

  {
    assert((po::polynomial{{2, {2}}} + D(po::polynomial{{1, {3}}}, 0))(1) == 5);

    PO_LINE;
  }
}
