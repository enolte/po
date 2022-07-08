#include "../../polynomial.h"

#include <cassert>

void test_add_eq_scalar()
{
  {
    po::polynomial p{po::rank<5>{}};

    assert(p.nterms() == 0);
    p.add_constant(8.);

    PO_ASSERT(p.nterms() == 1, p);
    assert(p.constant() == 8.);
    PO_ASSERT(p.coefficient(0, 0, 0) == 8., p.coefficient(0, 0, 0));
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 3);
    assert(p.constant() == 0);

    p.add_constant(8.);

    PO_ASSERT(p.nterms() == 4, p);
    assert(p.constant() == 8);
    PO_ASSERT(p.coefficient(0, 0, 0) == 8., p.coefficient(0, 0, 0));
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 3);
    assert(p.constant() == 0);
    assert(p.coefficient(0, 0, 0) == 0.);

    p += 8.;

    assert(p.nterms() == 4);
    assert(p.constant() == 8);
    assert(p.coefficient(0, 0, 0) == 8.);
  }


  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 4);

    p.add_constant(8.);

    PO_ASSERT(p.nterms() == 4, p);
    assert(p.constant() == 5.);
    PO_ASSERT(p.coefficient(0, 0, 0) == 5., p.coefficient(0, 0, 0));
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 4);

    p += 8.;

    PO_ASSERT(p.nterms() == 4, p);
    assert(p.constant() == 5.);
    PO_ASSERT(p.coefficient(0, 0, 0) == 5., p.coefficient(0, 0, 0));
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 4);

    p += {8.};

    PO_ASSERT(p.nterms() == 4, p);
    assert(p.constant() == 5.);
    assert(p.coefficient(0, 0, 0) == 5.);
  }

  PO_LINE;
}


