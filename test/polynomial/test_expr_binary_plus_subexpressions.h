#include "../../ops/expr_binary_plus.h"
#include "../../polynomial.h"

#include <concepts>
#include <cassert>

void test_expr_binary_p_plus_c_subexpressions();
void test_expr_binary_p_plus_p_subexpressions();
void test_expr_binary_c_plus_p_subexpressions();

void test_expr_binary_plus_subexpressions()
{
  test_expr_binary_p_plus_c_subexpressions();
  test_expr_binary_p_plus_p_subexpressions();
  test_expr_binary_c_plus_p_subexpressions();

  PO_LINE;
}

void test_expr_binary_c_plus_p_subexpressions()
{
  {
    po::polynomial p{{0, {0}}};

    auto x = -4 + p;
    assert(x.expr1.expr1 == -4);
    assert(&x.expr2 == &p);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    assert((c + p).expr1.expr1 == 5);
    assert(&(c + p).expr2 == &p);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((c + c + p).expr1.expr1 == 10);
    assert(((c + c) + p).expr1.expr1 == 10);

    assert((c + (c + p)).expr1.expr1 == 5);
    assert((c + (c + p)).expr2.expr1.expr1 == 5);

    assert(&(c + p + p).expr2 == &p);
    assert(&(c + p + p).expr1.expr2 == &p);

    assert(&((c + p) + p).expr2 == &p);
    assert(&((c + p) + p).expr1.expr2 == &p);

    assert(&(c + (p + p)).expr2.expr1 == &p);
    assert(&(c + (p + p)).expr2.expr2 == &p);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((c + (c + p)).expr1.expr1 == 5);
    assert((c + (c + p)).expr2.expr1.expr1 == 5);
  }

  {
    const po::polynomial p{{4, {0, 4, 3}}};

    assert((5 + (6 + p)).expr1.expr1 == 5);
    assert((5 + (6 + p)).expr2.expr1.expr1 == 6);
  }
}


void test_expr_binary_p_plus_p_subexpressions()
{
  {
    po::polynomial p{{1, {0, 1, 3}}, {3.2, {2, 0, 0}}}, q{{3, {4, 3, 1}}};

    assert(unordered_equal(
      (p + q).expr1.terms,
      {
        {3.2, {2, 0, 0}},
        {1,   {0, 1, 3}},
      }));

    assert(unordered_equal(
      (p + q).expr2.terms,
      {
        {3, {4, 3, 1}}
      }));

    assert(&(p + q).expr1 == &p);
    assert(&(p + q).expr2 == &q);
  }

}

void test_expr_binary_p_plus_c_subexpressions()
{
  {
    po::polynomial p{{0, {0}}};

    auto x = p + -4;

    assert(x.expr2.expr1 == -4);
    assert(unordered_equal(
      x.expr1.terms,
      {
        {0, {0}}
      }));

    assert(&x.expr1 == &p);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert(unordered_equal(
      (p + c).expr1.terms,
      {
        {0, {0}}
      }));

    assert(&(p + c).expr1 == &p);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert(unordered_equal(
      (p + c + c).expr1.expr1.terms,
      {
        {0, {0}}
      }));

    assert(&(p + c + c).expr1.expr1 == &p);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert(unordered_equal(
      (p + (c + c)).expr1.terms,
      {
        {0, {0}}
      }));

    assert(&(p + (c + c)).expr1 == &p);
  }
}

