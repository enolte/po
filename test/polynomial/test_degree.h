#include "../../polynomial.h"

void test_degree()
{
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

  PO_LINE;
}