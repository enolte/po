#include "../../ops/expr_partial_derivative.h"
#include "../../polynomial.h"

#include "../errors.h"

#include "test_expr_partial_derivative_static_asserts.h"

#include <concepts>
#include <cassert>

void test_Dp();
void test_DDp();

void test_expr_partial_derivative()
{
  test_Dp();
  PO_LINE;
}

void test_Dp()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    assert(po::D(p, 2)(1, 1, 1, 1) == dp2(1, 1, 1, 1));
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    assert(po::D(p, 2)(1, 3, -1.3, 2) == dp2(1, 3, -1.3, 2));
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    assert(po::D(p, 7)(1, 3, -1.3, 2) == p(1, 3, -1.3, 2));
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp0{{2, {0, 1, 1, 1}}, {0, {0, 4, 1, 0}}};

    assert(po::D(p, 0)(1, 3, -1.3, 2) == dp0(1, 3, -1.3, 2));
  }

}

#if 0
// TODO
void test_DDp()
{
  using po::D;

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2 {{2, {1, 1, 0, 1}}, {6 , {0, 4, 1, 0}}};
    po::polynomial dp21{{2, {1, 0, 0, 1}}, {24, {0, 3, 1, 0}}};

    assert(D(D(p, 2), 1)(1, 1, 1, 1) == dp21(1, 1, 1, 1));
  }
}

#endif


