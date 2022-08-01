#include "../../polynomial.h"

void test_op_D__c();
void test_op_D__p();

void test_op_D_plus_D__p();
void test_op_D_plus_D__c();
void test_op_c_plus_D__p();
void test_op_D_plus_c__p();

void test_op_D_plus_c__p_plus_p();

void test_expr_partial_derivative_subexpressions()
{
  test_op_D__c();
  test_op_D__p();

  // // test_op_c_plus_D__p();
  // test_op_D_plus_c__p();
  // test_op_D_plus_c__p_plus_p();

  test_op_D_plus_D__c();
  // // test_op_D_plus_D__p();

  PO_LINE;
}

void test_op_D__c()
{
  using po::D;

  {
    D(2)(4.3);
  }

  {
    D(2)(po::expr_constant{4.3});
  }

  {
    const po::expr_constant c{4.3};
    D(2)(c);
  }

  {
    const po::expr_constant c{4.3};
    D(2)(c)(3, 2, 1);
  }

  {
    const auto d1 = D(1);
  }

  {
    const po::pdo::PDO d1{1};
  }

  {
    const po::pdo::PDO d1 = D(1);
  }

  PO_FUNC;
}

void test_op_D__p()
{
  using po::D;

  {
    D(0);
  }

  {
    D(0)(po::polynomial{{1, {1, 0}}});
  }

  {
    const po::pdo::PDO d0 = D(0);

    const po::polynomial p{po::rank<15>{}};
    const po::polynomial q{po::rank<4>{}};
    const po::expr_partial_derivative dp0 = d0(p);
    const po::expr_partial_derivative dq0 = d0(q);
  }

  {
    po::polynomial p{{3, {2, 1}}};
    auto dp0 = D(0)(p);
  }

  {
    po::polynomial p{po::rank<15>{}};
    D(0)(p);
  }

  {
    po::polynomial p{po::rank<15>{}};
    D(0)(p)(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
  }

  PO_FUNC;
}



void test_op_D_plus_D__c()
{
  using po::D;

  {
    (D(0) + D(1))(2.7);
  }

  {
    (D(0) + D(1))(2.7)();
  }

  {
    (D(0) + D(1))(2.7)(1, 2);
  }

  PO_FUNC;
}
#if 0
void test_op_D_plus_D__p()
{
  using po::D;

  {
    D(0) + D(1);
  }

  {
    po::polynomial p{po::rank<15>{}};
    (D(0) + D(1))(p);
  }

  {
    po::polynomial p{po::rank<15>{}};
    (D(0) + D(6))(p)(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
  }
}

void test_op_c_plus_D__p()
{
  using po::D;

  {
    4 + D(0);
  }

  {
    po::polynomial p{{1, {3}}};
    (4 + D(0))(p);
  }

  {
    (4 + D(0))(po::polynomial{{1, {3}}});
  }

  {
    po::polynomial p{{1, {3}}};
    (4 + D(0))(p)(5.4);
  }
}

void test_op_D_plus_c__p()
{
  using po::D;

  {
    D(0) + 7;
  }

  {
    po::polynomial p{{1, {3}}};
    (D(0) + 7)(p);
  }

  {
    (D(0) + 7)(po::polynomial{{1, {3}}});
  }
PO_LINE;
  {
    po::polynomial p{{1, {3, 5}}};
    (D(0) + 7)(p)(5.4, 2);
  }
PO_LINE;
}

void test_op_D_plus_c__p_plus_p()
{
  using po::D;

  {
    po::polynomial p{{1, {3}}};
    po::polynomial q{{2, {4}}};
    auto x = p + q;
    static_assert(std::same_as<decltype(x), po::expr_binary_plus<po::polynomial&, po::polynomial&>>);
PO_LINE;
    (D(0) + 7)(x);
  }

  {
    po::polynomial p{{1, {3}}};
    po::polynomial q{{2, {4}}};
    auto x = p + q;
    static_assert(std::same_as<decltype(x), po::expr_binary_plus<po::polynomial&, po::polynomial&>>);
    (D(0) + 7)(std::move(x));
  }

  {
    po::polynomial p{{1, {3}}};
    po::polynomial q{{2, {4}}};
    (D(0) + 7)(p + q);
  }

  {
    (D(0) + 7)(po::polynomial{{1, {3}}} + po::polynomial{{2, {2}}});
  }

  {
    po::polynomial p{{1, {3, 5}}};
    po::polynomial q{{2, {4, 1}}};
    (D(0) + 7)(p + q)(5.4, 2);
  }
}

#endif
