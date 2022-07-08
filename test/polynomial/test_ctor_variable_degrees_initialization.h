#include "../../polynomial.h"

#include "compare.h"

#include <cassert>

void test_ctor_variable_degrees_initialization()
{
  {
    po::polynomial p{po::rank<0>{}};
    assert(equal(p.variable_degrees, {}));
  }

  {
    po::polynomial p{7.5, po::rank<0>{}};
    assert(equal(p.variable_degrees, {}));
  }

  {
    po::polynomial p{7.5, po::rank<6>{}};
    assert(equal(p.variable_degrees, 0, 0, 0, 0, 0, 0));
  }

  {
    using namespace po;
    polynomial p(rank<15>{});
    assert(p.variable_degrees.size() == 15);
    assert(equal(p.variable_degrees, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}};
    assert((equal(p.variable_degrees, 2, 3, 2, 1)));
  }
/*
  // Disabled for operator overload resolution
  {
    po::polynomial p{1.4, {2, 3, 2, 1}};
    assert((equal(p.variable_degrees, 2, 3, 2, 1)));
  }
*/
  {
    po::polynomial p({{1.4, {2, 3, 2, 1}}});
    assert((equal(p.variable_degrees, 2, 3, 2, 1)));
  }

  {
    po::polynomial p(1.4, 2, 3, 2, 1);
    assert((equal(p.variable_degrees, 2, 3, 2, 1)));
  }

  {
    po::polynomial p({{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}});
    assert((equal(p.variable_degrees, 4, 3, 4, 1)));
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};
    assert((equal(p.variable_degrees, 4, 3, 4, 1)));
  }

  PO_LINE;
}
