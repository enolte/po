#include "../../polynomial.h"

#include <cassert>

void test_expr_rank()
{
  {
    const po::scalar_type x = 7.5324;
    assert(po::expr_rank(x) == 0);
  }

  {
    po::polynomial p{{2, {1, 5, 4, 2, 0, 0, 1, 1}}};
    assert(po::expr_rank(p) == 8);
  }

  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = D(p, 0);
    assert(po::expr_rank(x) == 3);
  }

  {
    po::polynomial p{{2, {1, 5, 4, 2, 0, 0, 1, 1}}};
    auto x = -p;
    assert(po::expr_rank(x) == 8);
  }

  {
    po::polynomial p{{2, {1, 5, 4, 2, 0, 0, 1, 1}}};
    auto x = +p;
    assert(po::expr_rank(x) == 8);
  }

  {
    po::polynomial p{{2, {1, 5, 4, 2, 0, 0, 1, 1}}};
    auto x = -+-+p;
    assert(po::expr_rank(x) == 8);
  }

  {
    po::polynomial p{{2, {1, 5, 4, 2, 0, 0, 1, 1}}};
    auto x = p+5;
    assert(po::expr_rank(x) == 8);
  }

  {
    po::polynomial p{{2, {1, 5, 4, 0, 0, 1, 1}}};
    auto x = 5+p;
    assert(po::expr_rank(x) == 7);
  }

  {
    po::polynomial p{{2, {1, 5, 4, 2, 0, 0, 1, 1}}};
    auto x = 2*p;
    assert(po::expr_rank(x) == 8);
  }

  {
    po::polynomial p{{2, {1, 5, 1, 1}}};
    auto x = 2*p - p;
    assert(po::expr_rank(x) == 4);
  }

  {
    po::polynomial p{{2, {1, 5, 1, 1, 7}}}, q{{5.5, {9,8,9,8,6}}, {1.2, {0, 1, 2, 0, 4}}};
    auto x = 2*p*(p - q) - D(q*D(3*p*p - q*q*p, 3), 4);
    assert(po::expr_rank(x) == 5);
  }

  PO_LINE;
}


