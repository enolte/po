#include "../../polynomial.h"

void test_nterms()
{
  {
    po::polynomial p{po::rank<0>{}};
    assert(p.nterms() == 0);
  }

  {
    po::polynomial p{0., po::rank<0>{}};
    assert(p.nterms() == 1);
  }

  {
    po::polynomial p{7.5, po::rank<0>{}};
    assert(p.nterms() == 1);
  }

  {
    using namespace po;
    polynomial p(rank<15>{});
    assert(p.nterms() == 0);
  }

  {
    po::polynomial p
    {
      { 0.0, {0, 0, 0}},
      { 2.5, {1, 0, 0}},
      { 3.5, {1, 0, 1}},
      {-3.5, {2, 2, 2}}
    };

    assert(p.nterms() == 4);
  }

  {
    po::polynomial p
    {
      {-3.6, {1, 1, 4, 3, 0, 0, 4}},
      {-1.9, {8, 2, 0, 4, 0, 3, 3}},
      {12.5, {0, 5, 4, 0, 0, 1, 0}}
    };

    assert(p.nterms() == 3);

    assert(p.coefficient(8, 2, 0, 4, 0, 3, 3) == -1.9);
    assert(p.nterms() == 3);
    assert(p.coefficient(9, 4, 1, 1, 1, 1, 7) == 0.);

    // Non-constant access does not induce a new term when an exponent sequence is not found
    assert(p.nterms() == 3);
  }

  {
    const po::polynomial p
    {{-3.6, {1, 1, 4, 3, 0, 0, 4}},
     {-1.9, {8, 2, 0, 4, 0, 3, 3}},
     {12.5, {0, 5, 4, 0, 0, 1, 0}}};

    assert(p.nterms() == 3);

    assert(p.coefficient(8, 2, 0, 4, 0, 3, 3) == -1.9);
    assert(p.nterms() == 3);
    assert(p.coefficient(9, 4, 1, 1, 1, 1, 7) == 0.);

    assert(p.nterms() == 3);
  }

  PO_LINE;
}

