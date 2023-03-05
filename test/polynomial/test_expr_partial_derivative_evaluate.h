#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_Dc_evaluate();
void test_Dp_evaluate();

void test_Dc_plus_Dp__p_evaluate();

void test_unary_plus_Dp_evaluate();
void test_unary_minus_Dp_evaluate();

void test_c_plus_Dp_evaluate();
void test_Dc_plus_p_evaluate();
void test_Dp_plus_c_evaluate();

void test_D__p_plus_p_evaluate();
void test_D__c_plus_p_evaluate();
void test_D__p_plus_c_evaluate();
void test_D__level_2_evaluate();

void test_p_plus_unary_plus_Dp_evaluate();
void test_c_plus_unary_plus_Dp_evaluate();

void test_p_mult_Dp_evaluate();
void test_Dp_mult_p_evaluate();

void test_p_plus_Dp_evaluate();
void test_Dp_plus_p_evaluate();

void test_unary_plus_Dp_plus_c_evaluate();
void test_unary_plus_Dp_plus_p_evaluate();

void test_DDp_evaluate();
void test_DIp_evaluate();
void test_D__level_2_evaluate();

void test_expr_partial_derivative_evaluate()
{
  test_Dc_evaluate();
  test_Dp_evaluate();

  test_Dc_plus_Dp__p_evaluate();

  test_unary_plus_Dp_evaluate();
  test_unary_minus_Dp_evaluate();

  test_c_plus_Dp_evaluate();
  test_Dc_plus_p_evaluate();
  test_Dp_plus_c_evaluate();

  test_D__c_plus_p_evaluate();
  test_D__p_plus_p_evaluate();
  test_D__p_plus_c_evaluate();

  test_p_plus_unary_plus_Dp_evaluate();
  test_c_plus_unary_plus_Dp_evaluate();

  test_p_mult_Dp_evaluate();
  test_Dp_mult_p_evaluate();

  test_p_plus_Dp_evaluate();
  test_Dp_plus_p_evaluate();

  test_unary_plus_Dp_plus_c_evaluate();
  test_unary_plus_Dp_plus_p_evaluate();

  test_DDp_evaluate();
  test_DIp_evaluate();

  test_D__level_2_evaluate();

  PO_LINE;
}

void test_D__level_2_evaluate()
{
  {
    po::polynomial p{{1, {3}}}, q{{2, {2}}};
    assert(D(q + 2*p, 0)(-1) == -4 + 2*3);
  }

  {
    using P = po::polynomial;
    assert(D(P{{-7, {2}}} + P{{1, {3}}}, 0)(1) == -14 + 3);
  }

  {
    po::polynomial p{{1, {3, 3}}}, q{{2, {2, 1}}};

    assert(
      po_test::near_rel(
        D(q*p*p, 0)(2, 4.3),
        q(2, 4.3)*2*p(2, 4.3)*D(p, 0)(2, 4.3) + D(q, 0)(2, 4.3)*p(2, 4.3)*p(2, 4.3),
        0x1p-52));
  }
}

void test_Dc_evaluate()
{
  {
    po::expr_partial_derivative dc = po::D(3.2, 0);
    assert(dc(9.01) == 0);
  }

  {
    auto dc = po::D(3.2, 0);
    assert(dc(9.01) == 0);
  }

  {
    const po::expr_constant c{4.3};
    po::expr_partial_derivative dc = po::D(c, 2);
    assert(dc(9.01) == 0);
  }

  {
    po::expr_constant c{4.3};
    po::expr_partial_derivative dc = po::D(c, 2);
    assert(dc(9.01) == 0);
  }

  {
    po::expr_partial_derivative dc = po::D(po::expr_constant{4.3}, 2);
    assert(dc(9.01) == 0);
  }

  {
    assert(po::D(4.3, 2)(9.01) == 0);
  }
#if 0
  // TODO
  {
    assert(po::D(4, 2)(9.01) == 0);
  }
#endif
}

void test_Dp_evaluate()
{
  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = D(p, 0);
    assert(x(1, 1, 1) == 2);
  }

  {
    po::polynomial p{{2, {1, 1, 1}}};
    assert(D(p, 0)(1, 1, 1) == 2);
  }

  {
    po::polynomial p{{3, {2, 1}}};
    auto dp0 = po::D(p, 0);
    assert(dp0(3, 1.5) == 27);
  }

  {
    po::expr_partial_derivative dp0 = po::D(po::polynomial{{3, {2, 1}}}, 0);
    assert(dp0(2, 2) == 24);
  }

  {
    po::polynomial p{};
    assert(po::D(p, 4).place == 4);
  }

  {
    po::polynomial p  {{2, {1, 1, 1}}};
    assert(D(p, 0)(1, 1, 1) == 2);
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};

    assert(po::D(p, 7)(1, 3, -1.3, 2) == 0);
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp0{{2, {0, 1, 1, 1}}, {0, {0, 4, 1, 0}}};

    assert(po::D(p, 0)(1, 3, -1.3, 2) == dp0(1, 3, -1.3, 2));
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    PO_ASSERT(
      po::D(p, 2)(1, 1, 1, 1) == dp2(1, 1, 1, 1),
      po_test::errors(po::D(p, 2)(1, 1, 1, 1), dp2(1, 1, 1, 1), 0x1p-50));
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    PO_ASSERT(
      po_test::near_rel(po::D(p, 2)(1, 3, -1.3, 2), dp2(1, 3, -1.3, 2), 0x1p-51),
      po_test::errors(po::D(p, 2)(1, 3, -1.3, 2), dp2(1, 3, -1.3, 2), 0x1p-50));
  }
}

void test_unary_plus_Dp_evaluate()
{
  {
    po::polynomial p{{1, {3}}};
    +D(p, 0);
    assert((+D(p, 0))(1) == 3);
  }

  {
    assert((+D(po::polynomial{{1, {3}}}, 0))(1) == 3);
  }
}

void test_Dc_plus_p_evaluate()
{
  {
    po::polynomial p{{1, {3, 4}}};
    assert((po::D(2.3, 0) + p)(1, 2) == p(1, 2));
  }

  {
    assert((po::D(2.7, 0) + D(po::polynomial{{1, {3}}}, 0))(1) == 3);
  }
}

void test_c_plus_Dp_evaluate()
{
  {
    po::polynomial p{{1, {3}}};
    assert((4 + D(p, 0))(1) == 7);
  }

  {
    assert((4 + D(po::polynomial{{1, {3}}}, 0))(1) == 7);
  }
}

void test_D__c_plus_p_evaluate()
{
  {
    po::polynomial p{{1, {3}}};
    assert(D(4 + p, 0)(1) == 3);
    assert(D(4 + p, 0)(2) == 12);
  }

  {
    assert(D(4 + po::polynomial{{1, {3}}}, 0)(1) == 3);
    assert(D(4 + po::polynomial{{1, {3}}}, 0)(2) == 12);
  }
}

void test_D__p_plus_p_evaluate()
{
  {
    po::polynomial p{{1, {3}}}, q{{2, {2}}};
    assert(D(q + p, 0)(-1) == 3 + -4);
  }

  {
    assert(D(po::polynomial{{-7, {2}}} + po::polynomial{{1, {3}}}, 0)(1) == -14 + 3);
  }
}

void test_D__p_plus_c_evaluate()
{
  {
    po::polynomial p{{1, {3}}};
    assert((D(p - 7, 0))(1) == 3);
  }

  {
    assert((D(po::polynomial{{1, {3}}} + 2, 0))(1) == 3);
  }
}

void test_p_mult_Dp_evaluate()
{
  {
    po::polynomial p{{2, {4, 3}}};
    po::expr_partial_derivative dp1 = D(p, 1);

    assert( (p * dp1)(2, 1) ==  (2 * 16 * 1) * (6 * 16 * 1) );
  }

  {
    po::polynomial p  {{2, {1, 1, 1}}};

    const auto x = p * po::D(p, 2);
    x(1, 1, 1);
    PO_ASSERT(x(1, 1, 1) == 4, x(1, 1, 1));
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    const auto x = p * po::D(p, 2);

    assert(po::D(p, 2).place == 2);
    assert(po::D(p, 2)(1, 1, 1, 1) == 8);
    PO_ASSERT(
      po_test::near_rel(x(1, 1, 1, 1), 5*8, 0x1p-49),
      x(1, 1, 1, 1));
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    const auto x = p * po::D(p, 2);

    PO_ASSERT(
      po_test::near_rel(x(1, 1, 1, 1), (2 + 3)*(2 + 6), 0x1p-49),
      po_test::errors(x(1, 1, 1, 1), (2 + 3)*(2 + 6), 0x1p-49));

    PO_ASSERT(
      po_test::near_rel(x(1, 1, 1, 1), p(1, 1, 1, 1) * dp2(1, 1, 1, 1), 0x1p-50),
      po_test::errors(x(1, 1, 1, 1), p(1, 1, 1, 1) * po::D(p, 2)(1, 1, 1, 1), 0x1p-50));
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    using po::D;
    const auto x = p * D(p, 2);

    PO_ASSERT(
      x(1, 1, 1, 1) == p(1, 1, 1, 1) * dp2(1, 1, 1, 1),
      po_test::errors(x(1, 1, 1, 1), p(1, 1, 1, 1) * dp2(1, 1, 1, 1), 0x1p-50));
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    using po::D;

    PO_ASSERT(
      (p * D(p, 2))(1, 1, 1, 1) == p(1, 1, 1, 1) * dp2(1, 1, 1, 1),
      po_test::errors((p * D(p, 2))(1, 1, 1, 1), p(1, 1, 1, 1) * dp2(1, 1, 1, 1), 0x1p-50));
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    using po::D;

    PO_ASSERT(
      (p * D(p, 2))(1, 1.3, -0.01, 1) == p(1, 1.3, -0.01, 1) * dp2(1, 1.3, -0.01, 1),
      po_test::errors((p * D(p, 2))(1, 1.3, -0.01, 1), p(1, 1.3, -0.01, 1) * dp2(1, 1.3, -0.01, 1), 0x1p-50));
  }
}

void test_Dp_plus_c_evaluate()
{
  {
    po::polynomial p{{1, {3}}};
    assert((D(p, 0) - 7)(1) == -4);
  }

  {
    assert((D(po::polynomial{{1, {3}}}, 0) + 2)(1) == 5);
  }
}

void test_unary_minus_Dp_evaluate()
{
  {
    po::polynomial p{};
    -D(p, 0);
  }

  {
    po::polynomial p{{1, {3}}};
    auto x = -D(p, 0);
    assert(x.expr1(1) == 3);
    assert(x(1) == -3);
  }

  {
    po::polynomial p{{1, {3}}};
    -D(p, 0);
    assert((-D(p, 0))(1) == -3);
  }

  {
    assert((-D(po::polynomial{{1, {3}}}, 0))(1) == -3);
  }

}

void test_Dp_plus_p_evaluate()
{
  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = D(p, 0) + p;

    static_assert(std::same_as<
      decltype(x.expr1),
      const po::expr_partial_derivative<po::polynomial&>
    >);
  }
}


void test_p_plus_Dp_evaluate()
{
  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = p + D(p, 0);
  }

  {
    po::polynomial p{{1, {3}}};
    po::polynomial q{{2, {2}}};
    assert((q + D(p, 0))(1) == 5);
  }

  {
    po::polynomial q{{2, {2}}};
    assert((q + D(po::polynomial{{1, {3}}}, 0))(1) == 5);
  }

  {
    po::polynomial p{{1, {3}}};
    assert((po::polynomial{{2, {2}}} + D(p, 0))(1) == 5);
  }

  {
    assert((po::polynomial{{2, {2}}} + D(po::polynomial{{1, {3}}}, 0))(1) == 5);
  }
}

void test_c_plus_unary_plus_Dp_evaluate()
{
  {
    po::polynomial p{{1, {3}}};
    assert((4 + (+D(p, 0)))(1) == 7);
  }

  {
    assert((4 + (+D(po::polynomial{{1, {3}}}, 0)))(1) == 7);
  }
}


void test_p_plus_unary_plus_Dp_evaluate()
{
  {
    po::polynomial p{{1, {3}}};
    po::polynomial q{{2, {2}}};
    assert((q + +D(p, 0))(1) == 5);
  }

  {
    po::polynomial q{{2, {2}}};
    assert((q + (+D(po::polynomial{{1, {3}}}, 0)))(1) == 5);
  }

  {
    po::polynomial p{{1, {3}}};
    assert((po::polynomial{{2, {2}}} + +D(p, 0))(1) == 5);
  }

  {
    assert(
      (
        po::polynomial{{2, {2}}}
        +
        (+D(po::polynomial{{1, {3}}}, 0))
      )(1) == 5);
  }
}

void test_unary_plus_Dp_plus_p_evaluate()
{
  {
    po::polynomial p{{1, {3}}};
    po::polynomial q{{2, {2}}};
    assert(((+D(p, 0)) + q)(1) == 5);
  }

  {
    po::polynomial q{{2, {2}}};
    assert(((+(D(po::polynomial{{1, {3}}}, 0))) + q)(1) == 5);
  }

  {
    po::polynomial p{{1, {3}}};
    assert(((+D(p, 0)) + po::polynomial{{2, {2}}})(1) == 5);
  }

  {
    assert(
      (
        (+D(po::polynomial{{1, {3}}}, 0))
        +
        po::polynomial{{2, {2}}}
      )(1) == 5);
  }
}


void test_unary_plus_Dp_plus_c_evaluate()
{
  {
    po::polynomial p{{1, {3}}};
    assert((4 + (+D(p, 0)))(1) == 7);
  }

  {
    assert((4 + (+D(po::polynomial{{1, {3}}}, 0)))(1) == 7);
  }
}


void test_Dp_mult_p_evaluate()
{
  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = D(p, 0) * p;
    x.expr1(1, 1, 1);
  }

  {
    po::polynomial p{};

    using po::D;
    D(p, 0) * p;
  }

  {
    po::polynomial p{};

    using po::D;
    const auto x = D(p, 0) * p;
  }

  {
    po::polynomial p{};

    using po::D;
    const po::expr_binary_mult x = D(p, 0) * p;
    x.expr1(9);
  }

  {
    po::polynomial p{};
    p(9);
  }

  {
    po::polynomial p{};

    using po::D;
    const po::expr_binary_mult x = D(p, 0) * p;

    assert(po::is_polynomial<decltype(x.expr2)>);
    assert(x.expr2.nterms() == 0);
    // x.expr2(9);
  }

  {
    po::polynomial p{};

    using po::D;
    const po::expr_binary_mult x = D(p, 0) * p;
    // x(9);
  }

  {
    po::polynomial p{};

    using po::D;
    const auto x = D(p, 0) * p;
    x(9);
  }

  {
    po::polynomial p{};

    using po::D;
    (D(p, 0) * p)(3.5);
  }

  {
    po::polynomial p{{2, {1, 1, 1}}};
    assert((D(p, 0) * p)(1, 1, 1) == 4);
  }

  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = D(p, 0) * p;

    // PO_ASSERT(x(1, 1, 1) == (D(p, 0) * p)(1, 1, 1), x(1, 1, 1));
    PO_ASSERT(x(1, 1, 1) == 4, x(1, 1, 1));
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    PO_ASSERT(
      (D(p, 2) * p)(1, 1.3, -0.01, 1) == dp2(1, 1.3, -0.01, 1) * p(1, 1.3, -0.01, 1),
      po_test::errors(po::D(p, 2)(1, 1, 1, 1), dp2(1, 1, 1, 1), 0x1p-50));
  }

  {
    po::polynomial p  {{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2{{2, {1, 1, 0, 1}}, {6, {0, 4, 1, 0}}};

    const auto x = D(p, 2) * p;

    PO_ASSERT(
      po_test::near_rel(x(1, 1, 1, 1), p(1, 1, 1, 1) * dp2(1, 1, 1, 1), 0x1p-50),
      po_test::errors(x(1, 1, 1, 1), p(1, 1, 1, 1) * dp2(1, 1, 1, 1), 0x1p-50));
  }
}

void test_DDp_evaluate()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial dp2 {{2, {1, 1, 0, 1}}, {6 , {0, 4, 1, 0}}};
    po::polynomial dp21{{2, {1, 0, 0, 1}}, {24, {0, 3, 1, 0}}};

    PO_ASSERT(dp21(1, 1, 1, 1) == D(D(p, 2), 1)(1, 1, 1, 1),
      po_test::errors(D(D(p, 2), 1)(1, 1, 1, 1), dp21(1, 1, 1, 1), 0x1p-52));
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    assert(D(D(D(p, 2), 1), 3)(4, 0, 0, 0) == 8);
    assert(D(D(D(p, 2), 1), 3)(4, 1, 0, 0.215384) == 8);
  }
}


void test_DIp_evaluate()
{
  {
    po::polynomial     p{{2, {1, 1, 1, 1}}, { 3, {0, 4, 2, 0}}};
    // po::polynomial   a3p{{1, {1, 1, 1, 2}}, {6 , {0, 4, 2, 1}}}; // antiderivative(p) from in place 3
    po::polynomial   i3p{{3, {1, 1, 1,  }}, { 9, {0, 4, 2,  }}}; // integral(p) from -1 to 2 in place 3
    po::polynomial d2i3p{{3, {1, 1, 0,  }}, {18, {0, 4, 1,  }}}; // d(i2p)/dx2

    const double ex = d2i3p(1, 1, 1);
    const double ac = D(integral(p, {3, {-1, 2}}), 2)(1, 1, 1);

    assert(expr_rank(D(integral(p, {3, {-1, 2}}), 2)) == 3);

    PO_ASSERT(ac == ex, po_test::errors(ac, ex, 0x1p-52));
  }

}


void test_Dc_plus_Dp__p_evaluate()
{
  {
    assert((po::D(2.7, 0) + D(po::polynomial{{1, {3}}}, 0))(1) == 3);
  }
}

