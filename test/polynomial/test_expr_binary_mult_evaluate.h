#include "../../ops/expr_binary_mult.h"
#include "../../polynomial.h"

#include "../errors.h"

#include <concepts>
#include <cassert>

void test_expr_binary_mult_p_times_c();
void test_expr_binary_mult_p_times_p();
void test_expr_binary_mult_c_times_p();

void test_expr_binary_mult_evaluate()
{
  test_expr_binary_mult_p_times_c();
  test_expr_binary_mult_p_times_p();
  test_expr_binary_mult_c_times_p();

  PO_LINE;
}

void test_expr_binary_mult_p_times_p()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert((p*q)(4, 3, 3.4, 8) == p(4, 3, 3.4, 8) * q(4, 3, 3.4, 8));
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert((p*q*q)(4, 3, 3.4, 8) == p(4, 3, 3.4, 8) * q(4, 3, 3.4, 8) * q(4, 3, 3.4, 8));

    const double left = (p*q*q)(0.4, 3, 0.34, 8);
    const double right= p(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8);

    PO_ASSERT(
      left == right,
      po_test::errors(left, right, 0x1p-52));
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert(((p*q)*q)(4, 3, 3.4, 8) == p(4, 3, 3.4, 8) * q(4, 3, 3.4, 8) * q(4, 3, 3.4, 8));

    const double left = ((p*q)*q)(0.4, 3, 0.34, 8);
    const double right= p(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8);

    PO_ASSERT(
      left == right,
      po_test::errors(left, right, 0x1p-52));
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    const double left = (p*(q*q))(0.4, 3, 0.34, 8);
    const double right= p(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8);

    PO_ASSERT(
      po_test::near_rel(left, right, 0x1p-52),
      po_test::errors(left, right, 0x1p-52));
  }

  {
    const po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    const po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    const double left = (p*(q*q))(0.4, 3, 0.34, 8);
    const double right= p(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8);

    PO_ASSERT(
      po_test::near_rel(left, right, 0x1p-52),
      po_test::errors(left, right, 0x1p-52));
  }

}

void test_expr_binary_mult_c_times_p()
{
  {
    po::polynomial p{};
    auto x = -4 * p;
    assert(x.expr1.expr1 == -4);
  }

  {
    po::polynomial p{};
    auto x = 3ull * p;

    assert(x.expr1.expr1 == 3);
  }

  {
    po::polynomial p{po::rank<7>{}};
    auto x = 2*p;
    assert(x(1, 1, 1, 1, 1, 1, 1) == 0.);
    assert(x(0, 3, 2, 3, 7, 0, 2) == 0.);
  }

  {
    po::polynomial p{po::rank<7>{}};
    assert((2*p)(1, 1, 1, 1, 1, 1, 1) == 0.);
    assert((2*p)(0, 3, 2, 3, 7, 0, 2) == 0.);
  }


  {
    po::polynomial p{{3.2, {4, 5, 3, 5, 2}}};
    po::scalar_type c = 5;
    auto x = c * p;

    assert(x.expr1.expr1 == c);

    assert(x(1, 1, 1, 1, 1) == 16.);
  }
}

void test_expr_binary_mult_p_times_c()
{
  {
    po::polynomial p{{0, {0}}};
    auto x = p * -4;

    assert(x.expr2.expr1 == -4);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    auto x = p * c;

    assert(x.expr2.expr1 == c);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((p * c * c)(3) == 0);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((p * c * c)(3) == 0);
  }

  {
    const po::polynomial p{{4, {0, 4, 3}}};
    po::scalar_type c = 5;

    assert((p * c * c)(3, 2, 1) == (4 * 1 * 16 * 1) * 5 * 5);
  }
}

