#include "../../polynomial.h"

#include "test_expr_unary_plus_static_asserts.h"

#include <concepts>
#include <cassert>

void test_expr_unary_plus()
{
  {
    po::polynomial p{{7., {3, 2}}, {-5, {2, 1}}};

    assert((+p)(1, 1) == p(1, 1));
    assert((+p)(1.7, -0.238543873) == p(1.7, -0.238543873));
  }

  {
    const po::polynomial p{{7., {3, 2}}, {-5, {2, 1}}};

    assert((+p)(1, 1) == p(1, 1));
    assert((+p)(1.7, -0.238543873) == p(1.7, -0.238543873));
  }

  {
    const po::polynomial p{{7., {3, 2}}, {-5, {2, 1}}};
    const auto expr = +p;

    assert(expr(1, 1) == p(1, 1));
    assert((+p)(1, 1) == p(1, 1));
    assert((+p)(1.7, -0.238543873) == p(1.7, -0.238543873));
  }

  {
    po::polynomial p{{7., {3, 2}}, {-5, {2, 1}}};
    const auto expr = +p;

    assert(expr(1, 1) == p(1, 1));
    assert((+p)(1, 1) == p(1, 1));
    assert((+p)(1.7, -0.238543873) == p(1.7, -0.238543873));
  }

  {
    po::polynomial p{{7., {3, 2}}, {-5, {2, 1}}};
    auto expr = + +p;

    assert(expr(1, 1) == p(1, 1));
    assert((+ +p)(1, 1) == p(1, 1));
    assert((+ +p)(1.7, -0.238543873) == p(1.7, -0.238543873));
  }

  PO_LINE;
}
