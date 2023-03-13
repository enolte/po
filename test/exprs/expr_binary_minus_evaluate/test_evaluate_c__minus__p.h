#include "../../../polynomial.h"
#include "../../macros.h"
#include <cassert>

void test_evaluate_c__minus__p()
{
  {
    po::polynomial p{{0, {0}}};
    auto x = -4 - p;

    assert(x.expr1.expr1 == -4);
    assert((-4 - p)(7.3) == -4);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    auto x = c - p;

    assert(x.expr1.expr1 == c);
  }

  PO_LINE;
}
