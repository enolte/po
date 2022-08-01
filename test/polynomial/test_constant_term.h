#include "../../polynomial.h"

#include <cassert>

void test_constant_term()
{
  {
    // p(x, y, z) = x**3  -  4xy  -  3  +  2.5x
    po::polynomial p
    {
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    };

    assert(p.constant() == -3.);

    p.add(14, {0, 0, 0});

    assert(p.constant() == 11.);

    p.multiply(2., {1, 1, 1});

    assert(p.constant() == 0.);

    p.add(2.9, {0, 0, 0});

    assert(p.constant() == 2.9);
  }

  {
    po::polynomial k{po::rank<7>{}};
    for(std::size_t i = 0; i < 4; ++i)
      k += {double(3*i + 1), {i, i, i, 2*i, 0, 0, i}};

    k += {5.4, {0, 0, 0, 0, 0, 0, 0}};
    assert(k.constant() == 6.4);

    k.add(5.4, 0, 0, 0, 0, 0, 0, 0);
    assert(k.constant() == 11.8);
  }

  PO_LINE;
}

