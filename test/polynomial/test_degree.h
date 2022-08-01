#include "../../polynomial.h"

void test_degree()
{
  {
    po::polynomial p{{1, {2, 3}}, {2, {3, 4}}};

    assert(p.degree() == 7);
    assert(p.degree(0) == 3);
    assert(p.degree(1) == 4);
    PO_ASSERT(p.degree(2) == 0, p.degree(2));
    assert(p.degree(3) == 0);
    assert(p.degree(4) == 0);
  }

  {
    po::polynomial p({{0., {0, 0, 0}}, {3.2, {5, 2, 0}}, {12., {2, 0, 7}}});

    assert(p.degree() == 9);
    assert(p.degree(0) == 5);
    assert(p.degree(1) == 2);
    assert(p.degree(2) == 7);
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 7, 1, 5}}};

    assert(p.degree() == 14);
    assert(p.degree(0) == 3);
    assert(p.degree(1) == 7);
    assert(p.degree(2) == 3);
    assert(p.degree(3) == 5);
  }

  {
    po::polynomial p
    {{-3.6, {1, 1, 4, 3, 0, 0, 4}},
     {-1.9, {8, 2, 0, 4, 0, 3, 3}},
     {12.5, {0, 5, 4, 0, 0, 1, 0}}};

    assert(p.degree() == 20);
    assert(p.degree(3) == 4);
    assert(p.degree(4) == 0);
  }

  {
    const po::polynomial p
    {{-3.6, {1, 1, 4, 3, 0, 0, 4}},
     {-1.9, {8, 2, 0, 4, 0, 3, 3}},
     {12.5, {0, 5, 4, 0, 0, 1, 0}}};

    assert(p.degree() == 20);
    assert(p.degree(3) == 4);
    assert(p.degree(4) == 0);
  }


  PO_LINE;
}