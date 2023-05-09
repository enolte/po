#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_mult_eq_expr_level_1()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {7, {3, 0, 3, 2}}};

    p *= +q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 6, {3, 2, 5, 3}},
        {14, {4, 1, 4, 3}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 13, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {4, 2, 5, 3}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= std::move(6 - q);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {12, {1, 1, 1, 1}},
        {-6, {3, 2, 5, 3}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 13, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3, 2, 5, 3}), p.degrees());

    // TODO A move has no effect on a polynomial in a *= expression
    PO_ASSERT(compare::unordered_equal_terms(
      q,
      {
        {3, {2, 1, 4, 2}}
      }),
      q);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= q*q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {18, {5, 3, 9, 5}},
        {27, {4, 6,10, 4}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 24, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {5, 6,10, 5}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};

    p *= 6*p;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {24, {2, 2, 2, 2}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 8, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {2, 2, 2, 2}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};

    p *= 6*po::polynomial{{3, {2, 1, 4, 2}}};

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {36, {3, 2, 5, 3}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 13, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3, 2, 5, 3}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};

    p *= po::polynomial{{3, {2, 1, 4, 2}}} * 6;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {36, {3, 2, 5, 3}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 13, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3, 2, 5, 3}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p *= p*q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {12, {4, 3, 6, 4}},
        {36, {3, 6, 7, 3}},
        {27, {2, 9, 8, 2}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 21, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {4, 9, 8, 4}), p.degrees());

    PO_LINE;
  }
}
