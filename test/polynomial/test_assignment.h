#include "../../polynomial.h"
#include "compare.h"
#include <cassert>

void test_assign_polynomial();
void test_assign_init_list();
void test_assign_scalar();
void test_assign_expr_binary_plus();
void test_assign_expr_binary_minus();
void test_assign_expr_level_4();
void test_assign_expr_level_6();

void test_assignment()
{
  test_assign_polynomial();
  test_assign_init_list();
  test_assign_scalar();
  test_assign_expr_binary_plus();
  test_assign_expr_binary_minus();
  test_assign_expr_level_4();
  test_assign_expr_level_6();

  PO_LINE;
}

void test_assign_expr_binary_plus()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial v{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial q(1.4, po::rank<5>{});

    q = u + v;

    assert(q.rank() == 5);

    PO_ASSERT(unordered_equal(
      q.terms,
      {
        { 4.2, {4, 0, 7, 6, 5}},
        {18.5, {3, 1, 1, 0, 0}},
        { 1.2, {2, 2, 2, 2, 0}},
      }),
      q);

  }
}

void test_assign_expr_level_4()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial v{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial q(1.4, po::rank<2>{});

    q = u - 3*v*(-u);

    assert(q.rank() == 5);

    PO_ASSERT(unordered_near_rel(
      q.terms,
      {
        {  4.2 , {4, 0, 7, 6, 5}},
        {214.5 , {6, 2, 2, 0, 0}},
        { 19.8 , {5, 3, 3, 2, 0}},
        { 15.12, {6, 2, 9, 8, 5}},
        {  5.5 , {3, 1, 1, 0, 0}},
        {163.8 , {7, 1, 8, 6, 5}},
      }),
      q.terms);


    po::polynomial q2(1.4, po::rank<23>{});

    q2 = u + 3*v*u;

    assert(q2.rank() == 5);

    PO_ASSERT(unordered_equal(q.terms, q2.terms), q2);

  }
}

void test_assign_expr_level_6()
{
  {
    po::polynomial q{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial r{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial p(1.4, po::rank<2>{});

    p = 2*(r-3)*r*r - 3.2*q;

    assert(p.rank() == 5);

    PO_ASSERT(unordered_near_rel(
      p.terms,
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
  }
}

void test_assign_expr_binary_minus()
{
  {
    po::polynomial u{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial v{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial q(1.4, po::rank<5>{});

    q = u - v;

    assert(q.rank() == 5);

    PO_ASSERT(unordered_equal(
      q.terms,
      {
        { 4.2, {4, 0, 7, 6, 5}},
        {-7.5, {3, 1, 1, 0, 0}},
        {-1.2, {2, 2, 2, 2, 0}},
      }),
      q);

  }
}


void test_assign_polynomial()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    po::polynomial q(3.1, po::rank<6>{});

    q = p;

    assert(q == p);
    assert(q.rank() == 5);
  }

}

void test_assign_init_list()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    p = {{0.77, {2, 2, 2, 2, 2}}, {0.1, {1, 2, 3, 4, 5}}};

    assert(p.rank() == 5);
    assert(unordered_equal(
      p.terms,
      {
        {0.77, {2, 2, 2, 2, 2}},
        {0.1, {1, 2, 3, 4, 5}}
      }));
  }

}

void test_assign_scalar()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    p = 51.4;

    assert(p.rank() == 0);
    assert(unordered_equal(
      p.terms,
      {
        {51.4, {}}
      }));
  }

}