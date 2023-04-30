#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_ctor_variable_degrees_initialization()
{
  {
    po::polynomial p{po::polynomial::make_zero(po::rank<0>{})};
    assert(compare::equal(p.degrees(), {}));
    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_constant(po::rank<0>{}, 7.5)};
    assert(compare::equal(p.degrees(), {}));
    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_constant(po::rank<6>{}, 7.5)};
    assert(compare::equal(p.degrees(), {0, 0, 0, 0, 0, 0}));
    PO_LINE;
  }

  {
    using namespace po;
    polynomial p(po::polynomial::make_zero(rank<15>{}));
    assert(p.degrees().size() == 15);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    PO_LINE;
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}};
    assert((compare::equal(p.degrees(), {2, 3, 2, 1})));
    PO_LINE;
  }

  {
    po::polynomial p({{1.4, {2, 3, 2, 1}}});
    assert((compare::equal(p.degrees(), {2, 3, 2, 1})));
    PO_LINE;
  }

  {
    po::polynomial p({{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}});
    assert((compare::equal(p.degrees(), {4, 3, 4, 1})));
    PO_LINE;
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};
    assert((compare::equal(p.degrees(), {4, 3, 4, 1})));
    PO_LINE;
  }

  {
    po::polynomial p
    {
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    };

    assert(compare::equal(p.degrees(), {3, 1, 0}));
    PO_LINE;
  }
}
