#include "../../ops/expr_binary_plus.h"
#include "../../polynomial.h"

#include <concepts>
#include <cassert>

void test_expr_binary_p_plus_c_evaluate();
void test_expr_binary_p_plus_p_evaluate();
void test_expr_binary_c_plus_p_evaluate();

void test_expr_binary_plus_evaluate()
{
  test_expr_binary_p_plus_c_evaluate();
  test_expr_binary_p_plus_p_evaluate();
  test_expr_binary_c_plus_p_evaluate();

  PO_LINE;
}

void test_expr_binary_c_plus_p_evaluate()
{
  {
    po::polynomial p{{0, {0}}};

    auto x = -4 + p;

    assert(x(7.3) == -4);
  }

  {
    po::polynomial p{{0, {0}}};
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


void test_expr_binary_p_plus_p_evaluate()
{
  {
    po::polynomial p{{1, {0, 1, 3}}, {3.2, {2, 0, 0}}}, q{{3, {4, 3, 1}}};

    assert((p + q)(4, 3, 2 == p(4, 3, 2) + q(4, 3, 2)));
  }

}

void test_expr_binary_p_plus_c_evaluate()
{
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

