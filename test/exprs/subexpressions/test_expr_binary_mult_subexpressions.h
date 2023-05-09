#include "../../../polynomial.h"
#include <concepts>
#include <cassert>

void test_expr_binary_mult_p_times_c_subexpressions();
void test_expr_binary_mult_p_times_p_subexpressions();
void test_expr_binary_mult_c_times_p_subexpressions();

void test_expr_binary_mult_subexpressions()
{
  test_expr_binary_mult_p_times_c_subexpressions();
  test_expr_binary_mult_p_times_p_subexpressions();
  test_expr_binary_mult_c_times_p_subexpressions();
}

void test_expr_binary_mult_p_times_p_subexpressions()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert(&(p*q).expr1 == &p);
    assert(&(p*q).expr2 == &q);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert(&(p*q*q).expr1.expr1 == &p);
    assert(&(p*q*q).expr1.expr2 == &q);
    assert(&(p*q*q).expr2 == &q);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert(&((p*q)*q).expr1.expr1 == &p);
    assert(&((p*q)*q).expr1.expr2 == &q);
    assert(&((p*q)*q).expr2 == &q);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert(&(p*(q*q)).expr1 == &p);
    assert(&(p*(q*q)).expr2.expr1 == &q);
    assert(&(p*(q*q)).expr2.expr2 == &q);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    static_assert(
      std::same_as<
      decltype((std::move(p)*q*q).expr1.expr1),
      const po::polynomial>
    );

    // TODO Requires compiling with `-fpermissive`
    // assert(&(std::move(p)*(q*q)).expr1 != &p);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    // TODO Requires compiling with `-fpermissive`
    // assert(&(std::move(p)*(q*q)).expr1 != &p);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert(&(std::move(p)*(q*q)).expr2.expr1 == &q);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert(&(std::move(p)*(q*q)).expr2.expr2 == &q);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert(&(p*(std::move(q)*q)).expr1 == &p);
    assert(&(p*(std::move(q)*q)).expr2.expr2 == &q);

    PO_LINE;
  }
}

void test_expr_binary_mult_c_times_p_subexpressions()
{
  {
    po::polynomial p{};
    auto x = -4 * p;
    assert(x.expr1.expr1 == -4);
    assert(&x.expr2 == &p);
    static_assert(std::same_as<decltype(x.expr2), const po::polynomial&>);

    PO_LINE;
  }

  {
    po::polynomial p{};
    auto x = 3ull * p;

    assert(x.expr1.expr1 == 3);

    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_zero(po::rank<7>{})};
    auto x = 2*p;
    static_assert(std::same_as<decltype(x.expr2), const po::polynomial&>);

    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_zero(po::rank<7>{})};
    auto x = 2*std::move(p);
    assert(&x.expr2 != &p);
    static_assert(std::same_as<decltype(x.expr2), const po::polynomial>);

    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_zero(po::rank<7>{})};
    static_assert(std::same_as<decltype((2*p).expr2), const po::polynomial&>);

    PO_LINE;
  }

  {
    po::polynomial p{{2.3, {2, 1, 4}}, {0.4, {1, 1, 1}}};
    static_assert(std::same_as<decltype((2*std::move(p)).expr2), const po::polynomial>);

    // TODO Requires compiling with `-fpermissive`
    // assert(&(2*std::move(p)).expr2 != &p);

    // TODO
    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {2.3, {2, 1, 4}}, {0.4, {1, 1, 1}}
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{3.2, {4, 5, 3, 5, 2}}};
    po::scalar_type c = 5;
    auto x = c * p;

    // Constants are unconditionaly copied
    assert(&x.expr1.expr1 != &c);
    assert(x.expr1.expr1 == c);

    PO_LINE;
  }
}

void test_expr_binary_mult_p_times_c_subexpressions()
{
  {
    po::polynomial p{{0, {0}}};
    auto x = p * -4;

    assert(x.expr2.expr1 == -4);

    PO_LINE;
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    auto x = p * c;

    assert(x.expr2.expr1 == c);

    PO_LINE;
  }

  {
    po::polynomial p{{3, {0}}};
    po::scalar_type c = 5;

    assert(&(p * c * c).expr1.expr1 == &p);
    // TODO Requires compiling with `-fpermissive`
    // assert(&(p * c * c).expr1.expr2.expr1 != &c);
    // assert(&(p * c * c).expr2.expr1 != &c);

    PO_LINE;
  }

  {
    const po::polynomial p{{3, {0}}};
    po::scalar_type c = 5;

    assert(&(p * c * c).expr1.expr1 == &p);
    static_assert(std::same_as<
      decltype((p * c * c).expr1.expr2),
      const po::expr_constant
    >);

    static_assert(std::same_as<
      decltype((p * c * c).expr2),
      const po::expr_constant
    >);

    static_assert(std::same_as<
      decltype((p * c * c).expr1.expr1),
      const po::polynomial&
    >);

    PO_LINE;
  }

  {
    const po::polynomial p{{4, {0, 4, 3}}};
    po::scalar_type c = 5;

    assert(&(p * c * c).expr1.expr1 == &p);

    PO_LINE;
  }
}

