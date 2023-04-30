#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_mult_eq_nullary_expr_level_0()
{
  // Multiplying an empty zero-polynomial by a constant does not change polynomial storage.
  {
    po::polynomial p = po::polynomial::make_zero(po::rank<4>{});

    assert(p.nterms() == 0);
    assert(p.coefficient(0, 0, 0, 0) == 0.);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0}));
    assert(p.constant() == 0.);

    p *= po::expr_constant{0.5};

    assert(p.nterms() == 0);
    assert(p.coefficient(0, 0, 0, 0) == 0.);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0}));
    assert(p.constant() == 0.);

    PO_LINE;
  }

  // Multiplying a non-empty zero-polynomial by a constant does not change polynomial storage.
  {
    po::polynomial p = po::polynomial::make_constant(po::rank<4>{}, 0.);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 0. , {0, 0, 0, 0}},
      }),
      p);

    assert(p.nterms() == 1);
    assert(p.coefficient(0, 0, 0, 0) == 0.);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0}));
    assert(p.constant() == 0.);

    p *= po::expr_constant{0.5};

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 0. , {0, 0, 0, 0}},
      }),
      p);

    assert(p.nterms() == 1);
    assert(p.coefficient(0, 0, 0, 0) == 0.);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0}));
    assert(p.constant() == 0.);

    PO_LINE;
  }

  {
    po::polynomial p
    ({
      { 1. , {3, 0, 0, 7}},
      {-4  , {1, 1, 0, 3}},
      {-3  , {0, 0, 0, 7}},
      { 3  , {0, 0, 0, 0}},
      { 2.5, {1, 0, 0, 6}}
    });

    assert(p.constant() == 3.);
    assert(p.coefficient(1, 1, 0, 3) == -4.0);
    assert(compare::equal(p.degrees(), {3, 1, 0, 7}));

    p *= po::expr_constant{0.5};

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {0.5 *  1. , {3, 0, 0, 7}},
        {0.5 * -4  , {1, 1, 0, 3}},
        {0.5 * -3  , {0, 0, 0, 7}},
        {0.5 *  3  , {0, 0, 0, 0}},
        {0.5 *  2.5, {1, 0, 0, 6}}
      }),
      p);

    assert(p.coefficient(1, 1, 0, 3) == -2.0);
    assert(compare::equal(p.degrees(), {3, 1, 0, 7}));
    assert(p.constant() == 1.5);

    PO_LINE;
  }
}

