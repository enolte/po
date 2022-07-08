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
    PO_ASSERT(equal(p.variable_degrees, 3, 5, 2), p.variable_degrees);


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
    PO_ASSERT(equal(p.variable_degrees, 3, 5, 2), p.variable_degrees);

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
    PO_ASSERT(equal(p.variable_degrees, 3, 5, 2), p.variable_degrees);


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
    PO_ASSERT(equal(p.variable_degrees, 3, 5, 2), p.variable_degrees);

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
    PO_ASSERT(equal(p.variable_degrees, 3, 5, 2), p.variable_degrees);


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
    PO_ASSERT(equal(p.variable_degrees, 3, 5, 2), p.variable_degrees);

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

