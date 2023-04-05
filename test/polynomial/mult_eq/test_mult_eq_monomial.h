#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_mult_eq_monomial()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};

    assert(compare::unordered_equal_terms(
      p,
      {
        {2, {1, 1, 1, 1}},
        {3, {0, 4, 2, 0}}
      })
    );

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 6, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {1, 4, 2, 1}), p.degrees());

    p *= {3, {2, 1, 4, 2}};

    assert(compare::unordered_equal_terms(
      p,
      {
        {6, {3, 2, 5, 3}},
        {9, {2, 5, 6, 2}}
      })
    );

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 15, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3, 5, 6, 3}), p.degrees());


    p *= {1, {1, 0, 0, 0}};

    assert(compare::unordered_equal_terms(
      p,
      {
        {6, {4, 2, 5, 3}},
        {9, {3, 5, 6, 2}}
      })
    );

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 16, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {4, 5, 6, 3}), p.degrees());

    PO_LINE;
  }

  {
    // p(x, y, z) = 3x**3  -  4xy  -  3  -  2.5x
    po::polynomial p
    {
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    };

    assert(p.nterms() == 4.);
    assert(p.coefficient(1, 0, 0) == 2.5);
    assert(compare::equal(p.degrees(), {3, 1, 0}));
    assert(p.constant() == -3.);

    PO_ASSERT(p.rank() == 3, p.rank());
    PO_ASSERT(p.degree() == 3, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3, 1, 0}), p.degrees());

    // p(x, y, z) <- (3x**3  -  4xy  -  3  -  2.5x) * 2.5x

    p *= {2.5, {1, 0, 0}};

    // p(x, y, z) = 7.5x**4  -  10x**2y  -  7.5x  -  6.25x**2
    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {  2.5 , {4, 0, 0}},
        {-10.  , {2, 1, 0}},
        { -7.5 , {1, 0, 0}},
        {  6.25, {2, 0, 0}}
      }),
      p);

    assert(p.nterms() == 4);
    assert(p.coefficient(1, 0, 0) == -7.5);
    assert(compare::equal(p.degrees(), {4, 1, 0}));
    assert(p.constant() == 0.);

    PO_ASSERT(p.rank() == 3, p.rank());
    PO_ASSERT(p.degree() == 4, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {4, 1, 0}), p.degrees());

    PO_LINE;
  }

  {
    // p(x, y, z) = 3x**3  -  4xy  -  3  -  2.5x
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 4.);
    assert(p.coefficient(1, 0, 0) == 2.5);
    assert(p.constant() == -3.);

    PO_ASSERT(p.rank() == 3, p.rank());
    PO_ASSERT(p.degree() == 3, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3, 1, 0}), p.degrees());

    // p(x, y, z) <- (3x**3  -  4xy  -  3  -  2.5x) * 2.5x
    p *= {2.5, {1, 0, 0}};
    const po::monomial m{2.5, {1, 0, 0}};

    // p(x, y, z) = 7.5x**4  -  10x**2y  -  7.5x  -  6.25x**2
    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {  2.5 , {4, 0, 0}},
        {-10.  , {2, 1, 0}},
        { -7.5 , {1, 0, 0}},
        {  6.25, {2, 0, 0}}
      }),
      p);

    assert(p.nterms() == 4);
    assert(p.coefficient(1, 0, 0) == -7.5);
    assert(p.constant() == 0.);

    PO_ASSERT(p.rank() == 3, p.rank());
    PO_ASSERT(p.degree() == 4, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {4, 1, 0}), p.degrees());

    p *= {2.5, {1, 7, 0}};
    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {  6.25 , {5, 7, 0}},
        {-25.   , {3, 8, 0}},
        {-18.75 , {2, 7, 0}},
        { 15.625, {3, 7, 0}}
      }),
      p);

    assert(p.nterms() == 4);
    assert(p.coefficient(1, 7, 0) == 0.);
    assert(compare::equal(p.degrees(), {5, 8, 0}));
    assert(p.constant() == 0.);

    PO_ASSERT(p.rank() == 3, p.rank());
    PO_ASSERT(p.degree() == 12, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {5, 8, 0}), p.degrees());

    PO_LINE;
  }

  {
    // p(x, y, z) = 3x**3  -  4xy  -  3  +  2.5x
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(p.constant() == -3.);

    p *= {2., {0, 2, 3}};
    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {-8 , {1, 3, 3}},
        { 2., {3, 2, 3}},
        {-6 , {0, 2, 3}},
        { 5 , {1, 2, 3}}
      }),
      p);

    assert(p.coefficient(0, 2, 3) == -6.);
    assert(compare::equal(p.degrees(), {3, 3, 3}));
    assert(p.constant() == 0.);

    PO_ASSERT(p.rank() == 3, p.rank());
    PO_ASSERT(p.degree() == 8, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3, 3, 3}), p.degrees());

    PO_LINE;
  }
}

