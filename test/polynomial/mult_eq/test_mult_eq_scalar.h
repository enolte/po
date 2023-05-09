#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_mult_eq_scalar()
{

  // Multiplying an empty zero-polynomial by a constant does not change polynomial storage.
  {
    po::polynomial p = po::polynomial::make_zero(po::rank<4>{});

    assert(p.nterms() == 0);
    assert(p.coefficient(0, 0, 0, 0) == 0.);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0}));
    assert(p.constant() == 0.);

    static_assert(po::is_scalar<decltype(2)>);

    p *= 2;

    assert(p.nterms() == 0);
    assert(p.coefficient(0, 0, 0, 0) == 0.);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0}));
    assert(p.constant() == 0.);

    PO_LINE;
  }

  // Multiplying an empty zero-polynomial by a constant does not change polynomial storage.
  {
    po::polynomial p = po::polynomial::make_zero(po::rank<4>{});

    assert(p.nterms() == 0);
    assert(p.coefficient(0, 0, 0, 0) == 0.);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0}));
    assert(p.constant() == 0.);

    static_assert(po::is_scalar<decltype(2.)>);

    p *= 2.;

    assert(p.nterms() == 0);
    assert(p.coefficient(0, 0, 0, 0) == 0.);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0}));
    assert(p.constant() == 0.);

    PO_LINE;
  }

  // Multiplying an empty zero-polynomial by a constant does not change polynomial storage.
  {
    po::polynomial p = po::polynomial::make_zero(po::rank<4>{});

    assert(p.nterms() == 0);
    assert(p.coefficient(0, 0, 0, 0) == 0.);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0}));
    assert(p.constant() == 0.);

    p *= 0.5;

    assert(p.nterms() == 0);
    assert(p.coefficient(0, 0, 0, 0) == 0.);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0}));
    assert(p.constant() == 0.);

    PO_LINE;
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
    assert(compare::equal(p.degrees(), {3, 1, 0, 7}));

    p *= 0.5;
    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 0.5 , {3, 0, 0, 7}},
        { 1.5 , {0, 0, 0, 0}},
        {-2   , {1, 1, 0, 3}},
        {-1.5 , {0, 0, 0, 7}},
        { 1.25, {1, 0, 0, 6}}
      }),
      p);

    assert(p.coefficient(1, 1, 0) == -2.0);
    assert(compare::equal(p.degrees(), {3, 1, 0, 7}));
    assert(p.constant() == 1.5);

    PO_LINE;
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
    assert(compare::equal(p.degrees(), {3, 1, 0, 7}));

    p *= std::move(0.5);
    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 0.5 , {3, 0, 0, 7}},
        { 1.5 , {0, 0, 0, 0}},
        {-2   , {1, 1, 0, 3}},
        {-1.5 , {0, 0, 0, 7}},
        { 1.25, {1, 0, 0, 6}}
      }),
      p);

    assert(p.coefficient(1, 1, 0) == -2.0);
    assert(compare::equal(p.degrees(), {3, 1, 0, 7}));
    assert(p.constant() == 1.5);

    PO_LINE;
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
    assert(compare::equal(p.degrees(), {3, 1, 0, 7}));

    p *= {0.5};

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 0.5 , {3, 0, 0, 7}},
        { 1.5 , {0, 0, 0, 0}},
        {-2   , {1, 1, 0, 3}},
        {-1.5 , {0, 0, 0, 7}},
        { 1.25, {1, 0, 0, 6}}
      }),
      p);

    assert(p.coefficient(1, 1, 0) == -2.0);
    assert(compare::equal(p.degrees(), {3, 1, 0, 7}));
    assert(p.constant() == 1.5);

    PO_LINE;
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
    assert(compare::equal(p.degrees(), {3, 1, 0, 7}));

    const auto c = 0.5;
    p *= c;
    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 0.5 , {3, 0, 0, 7}},
        { 1.5 , {0, 0, 0, 0}},
        {-2   , {1, 1, 0, 3}},
        {-1.5 , {0, 0, 0, 7}},
        { 1.25, {1, 0, 0, 6}}
      }),
      p);

    assert(p.coefficient(1, 1, 0) == -2.0);
    assert(compare::equal(p.degrees(), {3, 1, 0, 7}));
    assert(p.constant() == 1.5);

    PO_LINE;
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
    assert(compare::equal(p.degrees(), {3, 1, 0, 7}));

    p *= 0.;
    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 0., {3, 0, 0, 7}},
        { 0., {0, 0, 0, 0}},
        { 0., {1, 1, 0, 3}},
        { 0., {0, 0, 0, 7}},
        { 0., {1, 0, 0, 6}}
      }),
      p);

    assert(p.coefficient(1, 1, 0) == 0.);
    assert(compare::equal(p.degrees(), {3, 1, 0, 7}));
    assert(p.constant() == 0.);

    PO_LINE;
  }
}

