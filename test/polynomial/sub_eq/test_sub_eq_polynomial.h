#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_sub_eq_polynomial()
{
  {
    po::polynomial p{po::rank<6>{}};
    po::polynomial q
    {
      {-3.2, {4, 1, 3, 2, 9, 3}},
      {-4.2, {4, 1, 4, 2, 9, 3}},
      {-5.2, {4, 1, 5, 2, 9, 3}},
      {-6.2, {4, 1, 6, 2, 9, 3}}
    };

    assert(p.nterms() == 0);

    p -= q;

    assert(compare::unordered_equal_terms(
      p,
      {
        {3.2, {4, 1, 3, 2, 9, 3}},
        {4.2, {4, 1, 4, 2, 9, 3}},
        {5.2, {4, 1, 5, 2, 9, 3}},
        {6.2, {4, 1, 6, 2, 9, 3}}
      }));

    assert(p.constant() == q.constant() && p.constant() == 0.);
    assert(p.rank() == q.rank() && p.rank() == 6);

    assert(p.degree() == q.degree());
    assert(compare::equal(p.degrees(), q.degrees()));

    PO_ASSERT(p.nterms() == 4, p);
    assert(p.constant() == 0.);
    PO_ASSERT(p.coefficient(0, 0, 0) == 0., p.coefficient(0, 0, 0));

    PO_LINE;
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {2.5, {1, 0, 0}}
    });

    po::polynomial q
    {
      {3.2, {3, 2, 9}},
      {4.2, {3, 0, 0}},
      {5.2, {0, 0, 0}},
      {6.2, {6, 2, 9}}
    };

    PO_ASSERT(p.nterms() == 3, p);
    assert(p.constant() == 0.);
    PO_ASSERT(p.coefficient(0, 0, 0) == 0., p.coefficient(0, 0, 0));

    PO_ASSERT(p.degree() == 3, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {3, 1, 0}), p.degrees());

    p -= q;

    PO_ASSERT(p.nterms() == 6, p);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {-3.2, {3, 0, 0}},
        {-5.2, {0, 0, 0}},
        {-4  , {1, 1, 0}},
        { 2.5, {1, 0, 0}},
        {-3.2, {3, 2, 9}},
        {-6.2, {6, 2, 9}}
      }),
      p);

    assert(p.constant() == -5.2);
    PO_ASSERT(p.coefficient(0, 0, 0) == -5.2, p.coefficient(0, 0, 0));

    PO_ASSERT(p.degree() == 17, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {6, 2, 9}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{po::rank<6>{}};
    po::polynomial q
    {
      {3.2, {4, 1, 3, 2, 9, 3}},
      {4.2, {4, 1, 4, 2, 9, 3}},
      {5.2, {4, 1, 5, 2, 9, 3}},
      {6.2, {4, 1, 6, 2, 9, 3}}
    };

    assert(p.nterms() == 0);

    p -= std::move(q);

    assert(compare::unordered_equal_terms(
      p,
      {
        {-3.2, {4, 1, 3, 2, 9, 3}},
        {-4.2, {4, 1, 4, 2, 9, 3}},
        {-5.2, {4, 1, 5, 2, 9, 3}},
        {-6.2, {4, 1, 6, 2, 9, 3}}
      }));

    assert(p.constant() == q.constant() && p.constant() == 0.);
    assert(p.rank() == q.rank() && p.rank() == 6);

    PO_ASSERT(p.degree() == 25, p.degree());
    assert(compare::equal(p.degrees(), q.degrees()));

    PO_ASSERT(p.nterms() == 4, p);
    assert(p.constant() == 0.);
    PO_ASSERT(p.coefficient(0, 0, 0) == 0., p.coefficient(0, 0, 0));

    PO_LINE;
  }
}


