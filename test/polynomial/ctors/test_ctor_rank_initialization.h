#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_ctor_rank_initialization()
{
  {
    po::polynomial p{7.5, po::rank<0>{}};
    assert(p.rank() == 0);
  }

  {
    po::polynomial p{0., po::rank<6>{}};
    assert(p.rank() == 6);
  }

  {
    po::polynomial p(7.5, po::rank<6>{});
    assert(p.rank() == 6);
    assert(p(3, 2.3, -0.7, 3, 13.65, 5) == 7.5);
  }

  {
    po::polynomial p{po::rank<15>{}};
    assert(p.rank() == 15);
  }

  {
    po::polynomial p(po::rank<15>{});
    assert(p.rank() == 15);
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}};
    assert(p.rank() == 4);
  }
/*
  // Disabled for operator overload resolution
  {
    po::polynomial p{1.4, {2, 3, 2, 1}};
    assert(p.rank() == 4);
  }

  {
    po::polynomial p({1.4, {2, 3, 2, 1}});
    assert(p.rank() == 4);
  }

  {
    po::polynomial p(1.4, {2, 3, 2, 1});
    assert(p.rank() == 4);
  }
*/
  {
    po::polynomial p({{1.4, {2, 3, 2, 1}}});
    assert(p.rank() == 4);
  }
/*
  {
    po::polynomial p(1.4, 2, 3, 2, 1);
    assert(p.rank() == 4);
  }

  {
    po::polynomial p{1.4, 2, 3, 2, 1};
    assert(p.rank() == 4);
  }
*/
  {
    po::polynomial p({{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}});
    assert(p.rank() == 4);
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
    assert(p.rank() == 4);
  }

  PO_LINE;
}
