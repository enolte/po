#include "../../ops/expr_binary_plus.h"
#include "../../polynomial.h"

#include <concepts>
#include <cassert>

#include "test_expr_binary_plus_static_asserts.h"

void test_expr_binary_p_plus_c();
void test_expr_binary_p_plus_p();
void test_expr_binary_c_plus_p();

void test_expr_binary_plus()
{
  test_expr_binary_p_plus_c();
  test_expr_binary_p_plus_p();
  test_expr_binary_c_plus_p();

  PO_LINE;
}

void test_expr_binary_c_plus_p()
{
  {
    po::polynomial p{{0, {0}}};

    auto x = -4 + p;

    assert(x.expr1.expr1 == -4);
    assert((-4 + p)(7.3) == -4);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    assert((c + p)(3) == c);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    assert((c + c + p)(3) == c + c);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    assert((c + c + p)(3) == c + c);
  }

  {
    const po::polynomial p{{4, {0, 4, 3}}};
    po::scalar_type c = 5;

    assert(((c + c) + p)(3, 2, 1) == (4 * 1 * 16 * 1) + 5 + 5);
    assert((c + (c + p))(3, 2, 1) == (4 * 1 * 16 * 1) + 5 + 5);
    assert((c + c + p)(3, 2, 1) == (4 * 1 * 16 * 1) + 5 + 5);
  }
}


void test_expr_binary_p_plus_p()
{
  {
    po::polynomial p{{1, {0, 1, 3}}, {3.2, {2, 0, 0}}}, q{{3, {4, 3, 1}}};

    assert((p + q)(4, 3, 2 == p(4, 3, 2) + q(4, 3, 2)));
  }

}

void test_expr_binary_p_plus_c()
{
  {
    po::polynomial p{{0, {0}}};

    auto x = p + -4;

    assert(x.expr2.expr1 == -4);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((p + c + c)(3) == c + c);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((p + c + c)(3) == c + c);
  }

  {
    const po::polynomial p{{4, {0, 4, 3}}};
    po::scalar_type c = 5;

    assert((p + c + c)(3, 2, 1) == (4 * 1 * 16 * 1) + 5 + 5);
  }
}

