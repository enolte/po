#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_ctor_rank_initialization()
{
  {
    po::polynomial p{po::polynomial::make_constant(po::rank<0>{}, 7.5)};
    assert(p.rank() == 0);
    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_zero(po::rank<6>{})};
    assert(p.rank() == 6);
    PO_LINE;
  }

  {
    po::polynomial p(po::polynomial::make_constant(po::rank<6>{}, 7.5));
    assert(p.rank() == 6);
    assert(p(3, 2.3, -0.7, 3, 13.65, 5) == 7.5);
    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_zero(po::rank<15>{})};
    assert(p.rank() == 15);
    PO_LINE;
  }

  {
    po::polynomial p(po::polynomial::make_zero(po::rank<15>{}));
    assert(p.rank() == 15);
    PO_LINE;
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}};
    assert(p.rank() == 4);
    PO_LINE;
  }

  {
    po::polynomial p({{1.4, {2, 3, 2, 1}}});
    assert(p.rank() == 4);
    PO_LINE;
  }

  {
    po::polynomial p({{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}});
    assert(p.rank() == 4);
    PO_LINE;
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
    assert(p.rank() == 4);
    PO_LINE;
  }
}
