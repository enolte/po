#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_A__p()
{
  // r-value polynomial, rank 0, place OOR
  {

    const auto x = po::antiderivative(po::polynomial{{6.7, {}}}, 5);

    assert(x.place == 5);
    assert(x.expr1.terms[0].coefficient == 6.7);

    po::polynomial p = po::instantiate(x);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {6.7, {0, 0, 0, 0, 0, 1}},
      }),
      p);

    PO_ASSERT(p.rank() == 6, p.rank());
    assert(compare::equal(p.degrees(), {0, 0, 0, 0, 0, 1}));
    assert(p.degree() == 1);

    assert(p.constant() == 0.);
    assert(p.coefficient(0, 0, 0, 0, 0, 1) == 6.7);

    PO_LINE;
  }

  // r-value polynomial, rank 1, place in range
  {
    const auto x = po::antiderivative(po::polynomial{{7.2, {2}}}, 0);

    assert(x.place == 0);
    PO_ASSERT(compare::unordered_equal_terms(x.expr1, {{7.2, {2}}}), x.expr1);

    po::polynomial p = instantiate(x);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {2.4, {3}},
      }),
      p);

    assert(p.rank() == 1);
    PO_ASSERT(compare::equal(p.degrees(), {3}), p.degrees());
    assert(p.degree() == 3);

    assert(p.constant() == 0.);
    assert(p.coefficient(3) == 2.4);

    PO_LINE;
  }

  // r-value polynomial, rank 1, place OOR
  {
    const auto x = po::antiderivative(po::polynomial{{7.2, {2}}}, 4);

    assert(x.place == 4);
    PO_ASSERT(compare::unordered_equal_terms(x.expr1, {{7.2, {2}}}), x.expr1);

    po::polynomial p = instantiate(x);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {7.2, {2, 0, 0, 0, 1}},
      }),
      p);

    assert(p.rank() == 5);
    PO_ASSERT(compare::equal(p.degrees(), {2, 0, 0, 0, 1}), p.degrees());
    assert(p.degree() == 3);

    assert(p.constant() == 0.);
    assert(p.coefficient(2, 0, 0, 0, 1) == 7.2);

    PO_LINE;
  }

  // r-value polynomial, rank 4, place OOR
  {
    const auto x = po::antiderivative(po::polynomial{{7.2, {2, 0, 9, 9}}}, 6);

    assert(x.place == 6);
    PO_ASSERT(compare::unordered_equal_terms(x.expr1, {{7.2, {2, 0, 9, 9}}}), x.expr1);

    po::polynomial p = instantiate(x);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {7.2, {2, 0, 9, 9, 0, 0, 1}},
      }),
      p);

    assert(p.rank() == 7);
    PO_ASSERT(compare::equal(p.degrees(), {2, 0, 9, 9, 0, 0, 1}), p.degrees());
    assert(p.degree() == 21);

    assert(p.constant() == 0.);
    assert(p.coefficient(2, 0, 9, 9, 0, 0, 1) == 7.2);

    PO_LINE;
  }


  // r-value polynomial, rank 4, multiple terms, place OOR
  {
    const auto x =
      po::antiderivative(
        po::polynomial
        {
          {7.2, {2, 0, 9, 9}},
          {0.1, {5, 1, 0, 3}},
          {1.2, {3, 3, 3, 2}},
        },
        6);

    assert(x.place == 6);
    PO_ASSERT(
      compare::unordered_equal_terms(
        x.expr1,
        {
          {7.2, {2, 0, 9, 9}},
          {0.1, {5, 1, 0, 3}},
          {1.2, {3, 3, 3, 2}},
        }),
        x.expr1);

    po::polynomial p = instantiate(x);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {7.2, {2, 0, 9, 9, 0, 0, 1}},
        {0.1, {5, 1, 0, 3, 0, 0, 1}},
        {1.2, {3, 3, 3, 2, 0, 0, 1}},
      }),
      p);

    assert(p.rank() == 7);
    PO_ASSERT(compare::equal(p.degrees(), {5, 3, 9, 9, 0, 0, 1}), p.degrees());
    assert(p.degree() == 21);

    assert(p.constant() == 0.);
    assert(p.coefficient(2, 0, 9, 9, 0, 0, 1) == 7.2);

    PO_LINE;
  }


  // r-value polynomial, rank 4, multiple terms, place in ragne
  {
    const auto x =
      po::antiderivative(
        po::polynomial
        {
          {7.2, {2, 0, 9, 9}},
          {0.1, {5, 1, 0, 3}},
          {1.2, {3, 3, 3, 2}},
        },
        2);

    assert(x.place == 2);
    PO_ASSERT(
      compare::unordered_equal_terms(
        x.expr1,
        {
          {7.2, {2, 0, 9, 9}},
          {0.1, {5, 1, 0, 3}},
          {1.2, {3, 3, 3, 2}},
        }),
        x.expr1);

    po::polynomial p = instantiate(x);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {0.72, {2, 0, 10, 9}},
        {0.1 , {5, 1,  1, 3}},
        {0.3 , {3, 3,  4, 2}},
      }),
      p);

    assert(p.rank() == 4);
    PO_ASSERT(compare::equal(p.degrees(), {5, 3, 10, 9}), p.degrees());
    assert(p.degree() == 21);

    assert(p.constant() == 0.);
    assert(p.coefficient(5, 1, 1, 3) == 0.1);

    PO_LINE;
  }
}

