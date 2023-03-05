#include "../../polynomial.h"

void test_mult_eq_expr_level_2();
void test_mult_eq_expr_level_3();
void test_mult_eq_expr_level_4();

void test_mult_eq_expr()
{
  test_mult_eq_expr_level_2();
  test_mult_eq_expr_level_3();
  test_mult_eq_expr_level_4();

  PO_LINE;
}

void test_mult_eq_expr_level_3()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    p *= q - 8.2*p;

    PO_ASSERT(unordered_near_rel(
      p.terms,
      {
        {  6  , {3, 2, 5, 3}},
        {  9  , {2, 5, 6, 2}},
        {  2  , {2, 1, 1, 1}},
        {-32.8, {2, 2, 2, 2}},
        {-98.4, {1, 5, 3, 1}},
        {-73.8, {0, 8, 4, 0}},
        {  3  , {1, 4, 2, 0}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 15, p.degree());
    PO_ASSERT(equal(p.degrees(), {3, 8, 6, 3}), p.degrees());
  }
}

void test_mult_eq_expr_level_4()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= q - 3*q + 2*q;

    PO_ASSERT(unordered_equal_terms(
      p,
      {
        {0, {3, 2, 5, 3}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 13, p.degree());
    PO_ASSERT(equal(p.degrees(), {3, 2, 5, 3}), p.degrees());
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= q - 4*q + 2*q;

    PO_ASSERT(unordered_equal_terms(
      p,
      {
        {-6, {3, 2, 5, 3}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 13, p.degree());
    PO_ASSERT(equal(p.degrees(), {3, 2, 5, 3}), p.degrees());
  }
}

void test_mult_eq_expr_level_2()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};

    p *= 2 + 6*po::polynomial{{3, {2, 1, 4, 2}}};

    PO_ASSERT(unordered_equal_terms(
      p,
      {
        {36, {3, 2, 5, 3}},
        { 4, {1, 1, 1, 1}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 13, p.degree());
    PO_ASSERT(equal(p.degrees(), {3, 2, 5, 3}), p.degrees());
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= std::move(6 - q);

    PO_ASSERT(unordered_equal(
      p.terms,
      {
        {12, {1, 1, 1, 1}},
        {-6, {3, 2, 5, 3}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 13, p.degree());
    PO_ASSERT(equal(p.degrees(), {3, 2, 5, 3}), p.degrees());

    // TODO A move has no effect on a polynomial in a *= expression
    PO_ASSERT(unordered_equal_terms(
      q,
      {
        {3, {2, 1, 4, 2}}
      }),
      q);
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= q*q;

    PO_ASSERT(unordered_equal(
      p.terms,
      {
        {18, {5, 3, 9, 5}},
        {27, {4, 6,10, 4}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 24, p.degree());
    PO_ASSERT(equal(p.degrees(), {5, 6,10, 5}), p.degrees());
  }

}