#include "../../polynomial.h"

#include <cassert>

void test_sub_eq_monomial()
{
  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 5, 0}},
      {-3 , {0, 0, 0}},
      {5.0, {1, 0, 0}},
      {1.7, {0, 3, 2}}
    });

    assert(p.nterms() == 5);
    assert(p.coefficient(1, 0, 0) == 5);
    PO_ASSERT(equal(p.degrees(), {3, 5, 2}), p.degrees());

    PO_ASSERT((unordered_equal(
      p.terms,
      {
        { 1., {3, 0, 0}},
        {-4 , {1, 5, 0}},
        {-3 , {0, 0, 0}},
        {5.0, {1, 0, 0}},
        {1.7, {0, 3, 2}},
      })),
      p);

    po::monomial m{-4 , {1, 5, 0}};

    p -= m;

    // Numerically cancelled terms are not removed.
    assert(p.nterms() == 5);
    PO_ASSERT(equal(p.degrees(), {3, 5, 2}), p.degrees());

    assert((unordered_equal(
      p.terms,
      {
        { 1., {3, 0, 0}},
        {-3 , {0, 0, 0}},
        {5.0, {1, 0, 0}},
        {1.7, {0, 3, 2}},
        {0.0, {1, 5, 0}},
      })));

    PO_ASSERT(equal(p.degrees(), {3, 5, 2}), p.degrees());
    PO_ASSERT(p.degree() == 6, p.degree());
    PO_ASSERT(p.rank() == 3, p.rank());
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 5, 0}},
      {-3 , {0, 0, 0}},
      {5.0, {1, 0, 0}},
      {1.7, {0, 3, 2}}
    });

    assert(p.nterms() == 5);
    assert(p.coefficient(1, 0, 0) == 5);
    PO_ASSERT(equal(p.degrees(), {3, 5, 2}), p.degrees());

    PO_ASSERT((unordered_equal(
      p.terms,
      {
        { 1., {3, 0, 0}},
        {-4 , {1, 5, 0}},
        {-3 , {0, 0, 0}},
        {5.0, {1, 0, 0}},
        {1.7, {0, 3, 2}},
      })),
      p);

    p -= {-4 , {1, 5, 0}};

    // Numerically cancelled terms are not removed.
    assert(p.nterms() == 5);
    PO_ASSERT(equal(p.degrees(), {3, 5, 2}), p.degrees());

    assert((unordered_equal(
      p.terms,
      {
        { 1., {3, 0, 0}},
        {-3 , {0, 0, 0}},
        {5.0, {1, 0, 0}},
        {1.7, {0, 3, 2}},
        {0.0, {1, 5, 0}},
      })));

    PO_ASSERT(p.rank() == 3, p.rank());
    PO_ASSERT(p.degree() == 6, p.degree());
    PO_ASSERT(equal(p.degrees(), {3, 5, 2}), p.degrees());

    // Zero coefficients are not ignored.
    PO_ASSERT(equal(p.degrees(), {3, 5, 2}), p.degrees());
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 5, 0}},
      {-3 , {0, 0, 0}},
      {5.0, {1, 0, 0}},
      {1.7, {0, 3, 2}}
    });

    assert(p.nterms() == 5);
    assert(p.coefficient(1, 0, 0) == 5);
    PO_ASSERT(equal(p.degrees(), {3, 5, 2}), p.degrees());

    PO_ASSERT((unordered_equal(
      p.terms,
      {
        { 1., {3, 0, 0}},
        {-4 , {1, 5, 0}},
        {-3 , {0, 0, 0}},
        {5.0, {1, 0, 0}},
        {1.7, {0, 3, 2}},
      })),
      p);

    p -= {{-4 , {1, 5, 0}}};

    // Numerically cancelled terms are not removed.
    assert(p.nterms() == 5);
    PO_ASSERT(equal(p.degrees(), {3, 5, 2}), p.degrees());
    PO_ASSERT(p.degree() == 6, p.degree());
    PO_ASSERT(p.rank() == 3, p.rank());

    assert((unordered_equal(
      p.terms,
      {
        { 1., {3, 0, 0}},
        {-3 , {0, 0, 0}},
        {5.0, {1, 0, 0}},
        {1.7, {0, 3, 2}},
        {0.0, {1, 5, 0}},
      })));
  }

  PO_LINE;
}

