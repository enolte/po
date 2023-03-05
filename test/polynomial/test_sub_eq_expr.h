#include "../../polynomial.h"

void test_sub_eq_expr_level_2();
void test_sub_eq_expr_level_3();
void test_sub_eq_expr_level_4();

void test_sub_eq_expr()
{
  test_sub_eq_expr_level_2();
  test_sub_eq_expr_level_3();
  test_sub_eq_expr_level_4();

  PO_LINE;
}

void test_sub_eq_expr_level_3()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    p -= q - 8.2*p;

    PO_ASSERT(unordered_near_rel(
      p.terms,
      {
        {18.4, {1, 1, 1, 1}},
        {27.6, {0, 4, 2, 0}},
        {  -3, {2, 1, 4, 2}},
        {  -1, {1, 0, 0, 0}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(equal(p.degrees(), {2, 4, 4, 2}), p.degrees());
  }
}

void test_sub_eq_expr_level_4()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p -= q - 3*q + 2*q;

    PO_ASSERT(unordered_equal_terms(
      p,
      {
        {2, {1, 1, 1, 1}},
        {0, {2, 1, 4, 2}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(equal(p.degrees(), {2, 1, 4, 2}), p.degrees());
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p -= q - 4*q + 2*q;

    PO_ASSERT(unordered_equal_terms(
      p,
      {
        {2, {1, 1, 1, 1}},
        {3, {2, 1, 4, 2}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(equal(p.degrees(), {2, 1, 4, 2}), p.degrees());
  }
}

void test_sub_eq_expr_level_2()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};

    p -= 2 + 6*po::polynomial{{3, {2, 1, 4, 2}}};

    PO_ASSERT(unordered_equal_terms(
      p,
      {
        { -2, {0, 0, 0, 0}},
        {  2, {1, 1, 1, 1}},
        {-18, {2, 1, 4, 2}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(equal(p.degrees(), {2, 1, 4, 2}), p.degrees());
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p -= std::move(6 - q);

    PO_ASSERT(unordered_equal(
      p.terms,
      {
        { 2, {1, 1, 1, 1}},
        {-6, {0, 0, 0, 0}},
        { 3, {2, 1, 4, 2}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(equal(p.degrees(), {2, 1, 4, 2}), p.degrees());

    // TODO A move has no effect on a polynomial in a -= expression
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

    p -= q*q;

    PO_ASSERT(unordered_equal(
      p.terms,
      {
        { 2, {1, 1, 1, 1}},
        { 3, {0, 4, 2, 0}},
        {-9, {4, 2, 8, 4}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 18, p.degree());
    PO_ASSERT(equal(p.degrees(), {4, 4, 8, 4}), p.degrees());
  }

}