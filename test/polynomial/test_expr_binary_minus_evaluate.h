#include "../../ops/expr_binary_minus.h"
#include "../../polynomial.h"

#include <cassert>

void test_expr_binary_p_minus_c();
void test_expr_binary_p_minus_p();
void test_expr_binary_c_minus_p();

void test_expr_binary_minus_evaluate()
{
  test_expr_binary_p_minus_c();
  test_expr_binary_p_minus_p();
  test_expr_binary_c_minus_p();

  PO_LINE;
}

void test_expr_binary_c_minus_p()
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
}

void test_expr_binary_p_minus_p()
{
  {
    po::polynomial p{{9, {1, 1, 0}}, {-.02, {6, 5, 4}}};

    assert((p-p)(3, 2.005, 8) == 0.);
  }
}

void test_expr_binary_p_minus_c()
{
  {
    po::polynomial p{{0, {0}}};
    auto x = p - -4;

    assert(x.expr2.expr1 == -4);
    assert(x(8) == 4);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    auto x = p - c;

    assert(x.expr2.expr1 == c);
    assert(x(8) == -5);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((p - c)(9.234) == -5);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((p - c - c)(3) == -c - c);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((p - c - c)(3) == -c - c);
  }

  {
    const po::polynomial p{{4, {0, 4, 3}}};
    po::scalar_type c = 5;

    assert((p - c - c)(3, 2, 1) == (4 * 1 * 16 * 1) - 5 - 5);
  }

}

