#include "../../polynomial.h"

void test_nterms()
{
  {
    po::polynomial p{po::polynomial::make_zero(po::rank<0>{})};
    assert(p.nterms() == 0);
    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_constant(po::rank<0>{}, 0.)};
    assert(p.nterms() == 1);
    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_constant(po::rank<0>{}, 7.5)};
    assert(p.nterms() == 1);
    PO_LINE;
  }

  {
    using namespace po;
    polynomial p(po::polynomial::make_zero(rank<15>{}));
    assert(p.nterms() == 0);
    PO_LINE;
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
    PO_LINE;
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
    PO_LINE;
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
    PO_LINE;
  }
}

