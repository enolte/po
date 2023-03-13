#include "../../polynomial.h"

void test_coefficient()
{
  {
    po::polynomial p{po::rank<0>{}};
    assert(p.coefficient() == 0);
  }

  {
    po::polynomial p{0., po::rank<0>{}};
    assert(p.coefficient() == 0);
  }

  {
    po::polynomial p{7.5, po::rank<0>{}};
    assert(p.coefficient() == 7.5);
  }

  {
    po::polynomial p{7.5, po::rank<6>{}};
    assert(compare::equal(p.degrees(), {0, 0, 0, 0, 0, 0}));

    assert(p.coefficient(0, 0, 0, 0, 0, 0) == 7.5);
    assert(p.coefficient(0, 3, 0, 0, 0, 0) == 0.0);
  }

  {
    po::polynomial p
     {{0.0, {0, 0, 0}},
      {2.5, {1, 0, 0}},
      {3.5, {1, 0, 1}},
      {-3.5, {2, 2, 2}}};

    assert(p.coefficient(1, 0, 1) == 3.5);
    assert(p.coefficient(1, 0, 0) == 2.5);
    assert(p.coefficient(0, 5, 0) == 0.);
    PO_ASSERT(p.coefficient(2, 2, 2) == -3.5, p);
  }

  {
    po::polynomial p
    {{-3.6, {1, 1, 4, 3, 0, 0, 4}},
     {-1.9, {8, 2, 0, 4, 0, 3, 3}},
     {12.5, {0, 5, 4, 0, 0, 1, 0}}};

    assert(p.nterms() == 3);

    assert(p.coefficient(8, 2, 0, 4, 0, 3, 3) == -1.9);
    assert(p.coefficient(9, 4, 1, 1, 1, 1, 7) == 0.);
  }

  {
    const po::polynomial p
    {{-3.6, {1, 1, 4, 3, 0, 0, 4}},
     {-1.9, {8, 2, 0, 4, 0, 3, 3}},
     {12.5, {0, 5, 4, 0, 0, 1, 0}}};

    assert(p.nterms() == 3);

    assert(p.coefficient(8, 2, 0, 4, 0, 3, 3) == -1.9);
    assert(p.coefficient(9, 4, 1, 1, 1, 1, 7) == 0.);
  }

  {
    po::polynomial p
    {
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    };

    assert(p.coefficient(1, 0, 0) == 2.5);
  }

  PO_LINE;
}

