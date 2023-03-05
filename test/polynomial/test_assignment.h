#include "../../polynomial.h"
#include "compare.h"
#include <cassert>

void test_assign_polynomial();
void test_assign_monomial_lvalue();
void test_assign_monomial_rvalue();
void test_assign_init_list();
void test_assign_scalar();

void test_assign_expr_unary_plus_level_1();
void test_assign_expr_unary_plus_level_5();

void test_assign_expr_unary_minus_level_1();
void test_assign_expr_unary_minus_level_7();

void test_assign_expr_binary_plus_level_1();
void test_assign_expr_binary_plus_level_3();

void test_assign_expr_binary_minus_level_1();

void test_assign_expr_level_4();
void test_assign_expr_level_6();

void test_assignment()
{
  test_assign_polynomial();
  test_assign_monomial_lvalue();
  test_assign_monomial_rvalue();
  test_assign_init_list();
  test_assign_scalar();

  test_assign_expr_unary_plus_level_1();
  test_assign_expr_unary_plus_level_5();

  test_assign_expr_unary_minus_level_1();
  test_assign_expr_unary_minus_level_7();

  test_assign_expr_binary_plus_level_1();
  test_assign_expr_binary_plus_level_3();

  test_assign_expr_binary_minus_level_1();

  test_assign_expr_level_4();
  test_assign_expr_level_6();

  PO_LINE;
}

void test_assign_expr_unary_plus_level_1()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};

    po::polynomial q(1.4, po::rank<5>{});

    PO_ASSERT(unordered_equal_terms(
      q,
      {
        {1.4, {0, 0, 0, 0, 0}}
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 0, q.degree());
    PO_ASSERT(equal(q.degrees(), {0, 0, 0, 0, 0}), q.degrees());

    q = +u;

    PO_ASSERT(unordered_equal_terms(
      q,
      {
        {4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 22, q.degree());
    PO_ASSERT(equal(q.degrees(), {4, 1, 7, 6, 5}), q.degrees());
  }
}

void test_assign_expr_unary_plus_level_5()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial v{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial q(1.4, po::rank<2>{});

    q = +(u - 3*v*(-u));

    PO_ASSERT(unordered_near_rel_terms(
      q,
      {
        {  4.2 , {4, 0, 7, 6, 5}},
        {214.5 , {6, 2, 2, 0, 0}},
        { 19.8 , {5, 3, 3, 2, 0}},
        { 15.12, {6, 2, 9, 8, 5}},
        {  5.5 , {3, 1, 1, 0, 0}},
        {163.8 , {7, 1, 8, 6, 5}},
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 30, q.degree());
    PO_ASSERT(equal(q.degrees(), {7, 3, 9, 8, 5}), q.degrees());

    po::polynomial q2(1.4, po::rank<23>{});

    q2 = u + 3*v*u;

    PO_ASSERT(unordered_equal_terms(q, q2.terms), q2);
    PO_ASSERT(q2.rank() == 5, q2.rank());
    PO_ASSERT(q2.degree() == 30, q2.degree());
    PO_ASSERT(equal(q2.degrees(), {7, 3, 9, 8, 5}), q2.degrees());

  }
}

void test_assign_expr_unary_minus_level_1()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};

    po::polynomial q(1.4, po::rank<9>{});

    PO_ASSERT(unordered_equal_terms(
      q,
      {
        {1.4, {0, 0, 0, 0, 0, 0, 0, 0, 0}}
      }),
      q);

    PO_ASSERT(q.rank() == 9, q.rank());
    PO_ASSERT(q.degree() == 0, q.degree());
    PO_ASSERT(equal(q.degrees(), {0, 0, 0, 0, 0, 0, 0, 0, 0}), q.degrees());

    q = -u;

    PO_ASSERT(unordered_equal_terms(
      q,
      {
        {-4.2, {4, 0, 7, 6, 5}}, { -5.5, {3, 1, 1, 0, 0}}
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 22, q.degree());
    PO_ASSERT(equal(q.degrees(), {4, 1, 7, 6, 5}), q.degrees());

  }
}

void test_assign_expr_unary_minus_level_7()
{
  {
    po::polynomial q{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial r{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial p(1.4, po::rank<2>{});

    p = -(2*(r-3)*r*r - 3.2*q);

    PO_ASSERT(unordered_near_rel_terms(
      p,
      {
        {-   3.456, {6, 6, 6, 6, 0}},
        {- 112.32 , {7, 5, 5, 4, 0}},
        {-1216.8  , {8, 4, 4, 2, 0}},
        {-4394    , {9, 3, 3, 0, 0}},
        {    8.64 , {4, 4, 4, 4, 0}},
        {  187.2  , {5, 3, 3, 2, 0}},
        { 1014    , {6, 2, 2, 0, 0}},
        {   13.44 , {4, 0, 7, 6, 5}},
        {   17.6  , {3, 1, 1, 0, 0}}
      }),
      p.terms);

    PO_ASSERT(p.rank() == 5, p.rank());
    PO_ASSERT(p.degree() == 24, p.degree());
    PO_ASSERT(equal(p.degrees(), {9, 6, 7, 6, 5}), p.degrees());


    po::polynomial p2(-(2*(r-3)*r*r - 3.2*q));

    PO_ASSERT(unordered_equal(p.terms, p2.terms), p2);
    PO_ASSERT(p.rank() == p2.rank(), p2.rank());
    PO_ASSERT(p.degree() == p2.degree(), p2.degree());
    PO_ASSERT(equal(p.degrees(), p2.degrees()), p2.degrees());
  }
}

void test_assign_expr_binary_plus_level_1()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial v{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial q(1.4, po::rank<5>{});

    PO_ASSERT(unordered_equal_terms(
      q,
      {
        {1.4, {0, 0, 0, 0, 0}}
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 0, q.degree());
    PO_ASSERT(equal(q.degrees(), {0, 0, 0, 0, 0}), q.degrees());

    q = u + v;

    PO_ASSERT(unordered_equal_terms(
      q,
      {
        { 4.2, {4, 0, 7, 6, 5}},
        {18.5, {3, 1, 1, 0, 0}},
        { 1.2, {2, 2, 2, 2, 0}},
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 22, q.degree());
    PO_ASSERT(equal(q.degrees(), {4, 2, 7, 6, 5}), q.degrees());
  }
}


void test_assign_expr_binary_plus_level_3()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial v{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial q(1.4, po::rank<5>{});

    PO_ASSERT(unordered_equal_terms(
      q,
      {
        {1.4, {0, 0, 0, 0, 0}}
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 0, q.degree());
    PO_ASSERT(equal(q.degrees(), {0, 0, 0, 0, 0}), q.degrees());

    q = u + v*(q-v);

    PO_ASSERT(unordered_equal_terms(
      q,
      {
        {   4.2 , {4,0,7,6,5}},
        {  23.7 , {3,1,1,0,0}},
        {   1.68, {2,2,2,2,0}},
        {  -1.44, {4,4,4,4,0}},
        { -31.2 , {5,3,3,2,0}},
        {-169   , {6,2,2,0,0}},
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 22, q.degree());
    PO_ASSERT(equal(q.degrees(), {6, 4, 7, 6, 5}), q.degrees());
  }
}


void test_assign_expr_level_4()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial v{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial q(1.4, po::rank<2>{});

    q = u - 3*v*(-u);

    PO_ASSERT(unordered_near_rel_terms(
      q,
      {
        {  4.2 , {4, 0, 7, 6, 5}},
        {214.5 , {6, 2, 2, 0, 0}},
        { 19.8 , {5, 3, 3, 2, 0}},
        { 15.12, {6, 2, 9, 8, 5}},
        {  5.5 , {3, 1, 1, 0, 0}},
        {163.8 , {7, 1, 8, 6, 5}},
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 30, q.degree());
    PO_ASSERT(equal(q.degrees(), {7, 3, 9, 8, 5}), q.degrees());

    po::polynomial q2(1.4, po::rank<23>{});

    q2 = u + 3*v*u;

    PO_ASSERT(unordered_equal_terms(q, q2.terms), q2);
    PO_ASSERT(q2.rank() == 5, q2.rank());
    PO_ASSERT(q2.degree() == 30, q2.degree());
    PO_ASSERT(equal(q2.degrees(), {7, 3, 9, 8, 5}), q2.degrees());
  }
}

void test_assign_expr_level_6()
{
  {
    po::polynomial q{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial r{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial p(1.4, po::rank<2>{});

    p = 2*(r-3)*r*r - 3.2*q;

    PO_ASSERT(unordered_near_rel_terms(
      p,
      {
        {    3.456, {6, 6, 6, 6, 0}},
        {  112.32 , {7, 5, 5, 4, 0}},
        { 1216.8  , {8, 4, 4, 2, 0}},
        { 4394    , {9, 3, 3, 0, 0}},
        {   -8.64 , {4, 4, 4, 4, 0}},
        { -187.2  , {5, 3, 3, 2, 0}},
        {-1014    , {6, 2, 2, 0, 0}},
        {  -13.44 , {4, 0, 7, 6, 5}},
        {  -17.6  , {3, 1, 1, 0, 0}}
      }),
      p.terms);

    PO_ASSERT(p.rank() == 5, p.rank());
    PO_ASSERT(p.degree() == 24, p.degree());
    PO_ASSERT(equal(p.degrees(), {9, 6, 7, 6, 5}), p.degrees());


    po::polynomial p2(2*(r-3)*r*r - 3.2*q);

    PO_ASSERT(unordered_equal(p.terms, p2.terms), p2);
    PO_ASSERT(p.rank() == p2.rank(), p2.rank());
    PO_ASSERT(p.degree() == p2.degree(), p2.degree());
    PO_ASSERT(equal(p.degrees(), p2.degrees()), p2.degrees());
  }
}

void test_assign_expr_binary_minus_level_1()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial v{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial q(1.4, po::rank<5>{});

    q = u - v;

    assert(q.rank() == 5);

    PO_ASSERT(unordered_equal_terms(
      q,
      {
        { 4.2, {4, 0, 7, 6, 5}},
        {-7.5, {3, 1, 1, 0, 0}},
        {-1.2, {2, 2, 2, 2, 0}},
      }),
      q);

    PO_ASSERT(q.rank() == 5, q.rank());
    PO_ASSERT(q.degree() == 22, q.degree());
    PO_ASSERT(equal(q.degrees(), {4, 2, 7, 6, 5}), q.degrees());
  }
}

void test_assign_monomial_lvalue()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    po::monomial m(3.1, {2, 5, 2});

    p = m;

    assert(unordered_equal_terms(
      p,
      {
        {3.1, {2, 5, 2}}
      }));

    assert(p.rank() == 3);
    assert(p.degree() == 9);
    PO_ASSERT(equal(p.degrees(), {2, 5, 2}), p.degrees());
  }
}

void test_assign_monomial_rvalue()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    po::monomial m(3.1, {2, 5, 2});

    p = std::move(m);

    assert(unordered_equal_terms(
      p,
      {
        {3.1, {2, 5, 2}}
      }));

    assert(p.rank() == 3);
    assert(p.degree() == 9);
    PO_ASSERT(equal(p.degrees(), {2, 5, 2}), p.degrees());
  }
}

void test_assign_polynomial()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    po::polynomial q(3.1, po::rank<6>{});

    q = p;

    assert(unordered_equal_terms(
      q,
      {
        {4.2, {4, 0, 7, 6, 5}},
        {5.5, {3, 1, 1, 0, 0}}
      }));

    assert(q == p);
    assert(q.rank() == 5);
    assert(q.degree() == 22);
    assert(equal(q.degrees(), {4, 1, 7, 6, 5}));
  }

}

void test_assign_init_list()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    p = {{0.77, {2, 2, 2, 2, 2}}, {0.1, {1, 2, 3, 4, 5}}};

    assert(unordered_equal_terms(
      p,
      {
        {0.77, {2, 2, 2, 2, 2}},
        {0.1 , {1, 2, 3, 4, 5}}
      }));

    assert(p.rank() == 5);
    assert(p.degree() == 15);
    assert(equal(p.degrees(), {2, 2, 3, 4, 5}));
  }

}

void test_assign_scalar()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    p = 51.4;

    assert(unordered_equal_terms(
      p,
      {
        {51.4, {}}
      }));

    assert(p.rank() == 0);
    assert(p.degree() == 0);
    assert(equal(p.degrees(), {}));
  }

}