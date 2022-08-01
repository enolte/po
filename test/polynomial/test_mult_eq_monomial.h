#include "../../polynomial.h"

#include <cassert>

void test_mult_eq_monomial()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};

    assert(unordered_equal(
      p.terms,
      {
        {2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}
      })
    );

    p *= {3, {2, 1, 4, 2}};

    assert(unordered_equal(
      p.terms,
      {
        {6, {3, 2, 5, 3}}, {9, {2, 5, 6, 2}}
      })
    );

    p *= {1, {1, 0, 0, 0}};

    assert(unordered_equal(
      p.terms,
      {
        {6, {4, 2, 5, 3}}, {9, {3, 5, 6, 2}}
      })
    );
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
    assert(compare::equal(p.variable_degrees, 3, 1, 0));
    assert(p.constant() == -3.);

    // p(x, y, z) <- (3x**3  -  4xy  -  3  -  2.5x) * 2.5x

    p *= {2.5, {1, 0, 0}};

    // p(x, y, z) = 7.5x**4  -  10x**2y  -  7.5x  -  6.25x**2
    PO_ASSERT(unordered_equal(
      p.terms,
      {
        {  2.5 , {4, 0, 0}},
        {-10.  , {2, 1, 0}},
        { -7.5 , {1, 0, 0}},
        {  6.25, {2, 0, 0}}
      }),
      p);

    assert(p.nterms() == 4);
    assert(p.coefficient(1, 0, 0) == -7.5);
    assert(compare::equal(p.variable_degrees, 4, 1, 0));
    assert(p.constant() == 0.);
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
    assert(compare::equal(p.variable_degrees, 3, 1, 0));
    assert(p.constant() == -3.);

    // p(x, y, z) <- (3x**3  -  4xy  -  3  -  2.5x) * 2.5x
    p *= {2.5, {1, 0, 0}};
    const po::monomial m{2.5, {1, 0, 0}};

    // p(x, y, z) = 7.5x**4  -  10x**2y  -  7.5x  -  6.25x**2
    PO_ASSERT(unordered_equal(
      p.terms,
      {
        {  2.5 , {4, 0, 0}},
        {-10.  , {2, 1, 0}},
        { -7.5 , {1, 0, 0}},
        {  6.25, {2, 0, 0}}
      }),
      p);

    assert(p.nterms() == 4);
    assert(p.coefficient(1, 0, 0) == -7.5);
    assert(compare::equal(p.variable_degrees, 4, 1, 0));
    assert(p.constant() == 0.);

    p *= {2.5, {1, 7, 0}};
    PO_ASSERT(unordered_equal(
      p.terms,
      {
        {  6.25 , {5, 7, 0}},
        {-25.   , {3, 8, 0}},
        {-18.75 , {2, 7, 0}},
        { 15.625, {3, 7, 0}}
      }),
      p);

    assert(p.nterms() == 4);
    assert(p.coefficient(1, 7, 0) == 0.);
    assert(compare::equal(p.variable_degrees, 5, 8, 0));
    assert(p.constant() == 0.);
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

    assert(p.constant() == -3.);

    p *= {2., {0, 2, 3}};
    PO_ASSERT(unordered_equal(
      p.terms,
      {
        {-8 , {1, 3, 3}},
        { 2., {3, 2, 3}},
        {-6 , {0, 2, 3}},
        { 5 , {1, 2, 3}}
      }),
      p);

    assert(p.coefficient(0, 2, 3) == -6.);
    assert(compare::equal(p.variable_degrees, 3, 3, 3));
    assert(p.constant() == 0.);
  }


  PO_LINE;
}

