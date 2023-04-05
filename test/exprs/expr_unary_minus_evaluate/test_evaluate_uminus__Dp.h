#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_uminus__Dp()
{
  {
    po::polynomial p{};
    -D(p, 0);

    PO_LINE;
  }

  {
    po::polynomial p{{1, {3}}};
    auto x = -D(p, 0);
    assert(x.expr1(1) == 3);
    assert(x(1) == -3);

    PO_LINE;
  }

  {
    po::polynomial p{{1, {3}}};
    -D(p, 0);
    assert((-D(p, 0))(1) == -3);

    PO_LINE;
  }

  {
    assert((-D(po::polynomial{{1, {3}}}, 0))(1) == -3);

    PO_LINE;
  }

}
