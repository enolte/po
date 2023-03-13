#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_ctor_constant_term_initialization()
{
  {
    po::polynomial p{po::rank<0>{}};
    assert(p.constant() == 0.);
  }

  {
    po::polynomial p(0, po::rank<0>{});
    assert(p.constant() == 0);
  }

  {
    po::polynomial p{7.5, po::rank<6>{}};
    assert(p.constant() == 7.5);
  }

  {
    using namespace po;
    polynomial p(rank<15>{});
    assert(p.constant() == 0.);
  }

  {
    po::polynomial p{{1.4, {0, 0, 0, 0}}};
    assert(p.constant() == 1.4);
  }

  {
    po::polynomial p({{1.4, {0, 0, 0, 0}}});
    assert(p.constant() == 1.4);
  }
/*
  // Disabled for operator overload resolution
  {
    po::polynomial p(1.4, {0, 0, 0, 0});
    assert(p.constant() == 1.4);
  }
*/
  {
    po::polynomial p({{2.4, {3, 2, 3, 2}}, {-0.6, {0, 0, 0, 0}}});
    assert(p.constant() == -0.6);
  }

  {
    po::polynomial p{{2.4, {0, 0, 0, 0}}, {-0.6, {1, 1, 1, 1}}};
    assert(p.constant() == 2.4);
  }

  {
    po::polynomial p{{2.4, {0, 0, 0, 0}}, {-1.2, {0, 0, 0, 0}}};
    PO_ASSERT(p.constant() == 1.2, p.constant());
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {47.2, {0, 0, 0, 0}}, {-0.6, {1, 1, 1, 1}}, {2., {0, 0, 0, 0}}};
    po::polynomial moved{std::move(p)};

    assert(moved.constant() == 49.2);
  }

  {
    po::polynomial p
    {
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    };

    assert(p.constant() == -3.);
  }

  PO_LINE;
}
