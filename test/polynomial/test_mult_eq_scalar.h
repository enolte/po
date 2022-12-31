#include "../../polynomial.h"

#include <cassert>

void test_mult_eq_scalar()
{
  {
    po::polynomial p
    ({
      { 1., {3, 0, 0, 7}},
      {-4 , {1, 1, 0, 3}},
      {-3 , {0, 0, 0, 7}},
      { 3 , {0, 0, 0, 0}},
      {2.5, {1, 0, 0, 6}}
    });

    assert(p.constant() == 3.);
    assert(p.coefficient(1, 1, 0) == -4.0);
    assert(compare::equal(p.degrees(), 3, 1, 0, 7));

    p *= 0.5;
    PO_ASSERT(unordered_equal(
      p.terms,
      {
        { 0.5 , {3, 0, 0, 7}},
        { 1.5 , {0, 0, 0, 0}},
        {-2   , {1, 1, 0, 3}},
        {-1.5 , {0, 0, 0, 7}},
        { 1.25, {1, 0, 0, 6}}
      }),
      p);

    assert(p.coefficient(1, 1, 0) == -2.0);
    assert(compare::equal(p.degrees(), 3, 1, 0, 7));
    assert(p.constant() == 1.5);
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0, 7}},
      {-4 , {1, 1, 0, 3}},
      {-3 , {0, 0, 0, 7}},
      { 3 , {0, 0, 0, 0}},
      {2.5, {1, 0, 0, 6}}
    });

    assert(p.constant() == 3.);
    assert(p.coefficient(1, 1, 0) == -4.0);
    assert(compare::equal(p.degrees(), 3, 1, 0, 7));

    p *= std::move(0.5);
    PO_ASSERT(unordered_equal(
      p.terms,
      {
        { 0.5 , {3, 0, 0, 7}},
        { 1.5 , {0, 0, 0, 0}},
        {-2   , {1, 1, 0, 3}},
        {-1.5 , {0, 0, 0, 7}},
        { 1.25, {1, 0, 0, 6}}
      }),
      p);

    assert(p.coefficient(1, 1, 0) == -2.0);
    assert(compare::equal(p.degrees(), 3, 1, 0, 7));
    assert(p.constant() == 1.5);
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0, 7}},
      {-4 , {1, 1, 0, 3}},
      {-3 , {0, 0, 0, 7}},
      { 3 , {0, 0, 0, 0}},
      {2.5, {1, 0, 0, 6}}
    });

    assert(p.constant() == 3.);
    assert(p.coefficient(1, 1, 0) == -4.0);
    assert(compare::equal(p.degrees(), 3, 1, 0, 7));

    p *= {0.5};
    PO_ASSERT(unordered_equal(
      p.terms,
      {
        { 0.5 , {3, 0, 0, 7}},
        { 1.5 , {0, 0, 0, 0}},
        {-2   , {1, 1, 0, 3}},
        {-1.5 , {0, 0, 0, 7}},
        { 1.25, {1, 0, 0, 6}}
      }),
      p);

    assert(p.coefficient(1, 1, 0) == -2.0);
    assert(compare::equal(p.degrees(), 3, 1, 0, 7));
    assert(p.constant() == 1.5);
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0, 7}},
      {-4 , {1, 1, 0, 3}},
      {-3 , {0, 0, 0, 7}},
      { 3 , {0, 0, 0, 0}},
      {2.5, {1, 0, 0, 6}}
    });

    assert(p.constant() == 3.);
    assert(p.coefficient(1, 1, 0) == -4.0);
    assert(compare::equal(p.degrees(), 3, 1, 0, 7));

    const auto c = 0.5;
    p *= c;
    PO_ASSERT(unordered_equal(
      p.terms,
      {
        { 0.5 , {3, 0, 0, 7}},
        { 1.5 , {0, 0, 0, 0}},
        {-2   , {1, 1, 0, 3}},
        {-1.5 , {0, 0, 0, 7}},
        { 1.25, {1, 0, 0, 6}}
      }),
      p);

    assert(p.coefficient(1, 1, 0) == -2.0);
    assert(compare::equal(p.degrees(), 3, 1, 0, 7));
    assert(p.constant() == 1.5);
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0, 7}},
      {-4 , {1, 1, 0, 3}},
      {-3 , {0, 0, 0, 7}},
      { 3 , {0, 0, 0, 0}},
      {2.5, {1, 0, 0, 6}}
    });

    assert(p.constant() == 3.);
    assert(p.coefficient(1, 1, 0) == -4.0);
    assert(compare::equal(p.degrees(), 3, 1, 0, 7));

    p *= 0.;
    PO_ASSERT(unordered_equal(
      p.terms,
      {
        { 0., {3, 0, 0, 7}},
        { 0., {0, 0, 0, 0}},
        { 0., {1, 1, 0, 3}},
        { 0., {0, 0, 0, 7}},
        { 0., {1, 0, 0, 6}}
      }),
      p);

    assert(p.coefficient(1, 1, 0) == 0.);
    assert(compare::equal(p.degrees(), 3, 1, 0, 7));
    assert(p.constant() == 0.);
  }

  PO_LINE;
}

