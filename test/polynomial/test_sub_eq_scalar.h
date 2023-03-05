#include "../../polynomial.h"

#include <cassert>

void test_sub_eq_scalar()
{
  {
    po::polynomial p{po::rank<5>{}};

    assert(p.nterms() == 0);
    assert(p.constant() == 0);
    assert(p.coefficient(0, 0, 0) == 0.);

    p -= 8.;

    assert(p.nterms() == 1);
    assert(p.constant() == -8.);
    assert(p.coefficient(0, 0, 0) == -8.);
  }

  {
    po::polynomial p
    ({
      { 1. , {3, 0, 0}},
      {-4  , {1, 1, 0}},
      { 2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 3);
    assert(p.constant() == 0);
    assert(p.coefficient(0, 0, 0) == 0.);

    p -= 8.;

    assert(p.nterms() == 4);
    assert(p.constant() == -8);
    assert(p.coefficient(0, 0, 0) == -8.);
  }


  {
    po::polynomial p
    ({
      { 1. , {3, 0, 0}},
      {-4  , {1, 1, 0}},
      {-3  , {0, 0, 0}},
      { 2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 4);
    assert(p.constant() == -3.);
    assert(p.coefficient(0, 0, 0) == -3.);

    p -= 8.;

    assert(p.nterms() == 4);
    assert(p.constant() == -11.);
    assert(p.coefficient(0, 0, 0) == -11.);
  }

  {
    po::polynomial p
    ({
      { 1. , {3, 0, 0}},
      {-4  , {1, 1, 0}},
      {-3  , {0, 0, 0}},
      { 2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 4);
    assert(p.constant() == -3.);
    assert(p.coefficient(0, 0, 0) == -3.);

    p -= {8.};

    assert(p.nterms() == 4);
    assert(p.constant() == -11.);
    assert(p.coefficient(0, 0, 0) == -11.);
  }

  PO_LINE;
}


