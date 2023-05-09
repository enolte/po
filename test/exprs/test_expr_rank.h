#include "../../polynomial.h"

#include <cassert>

void test_expr_rank()
{
  {
    const po::scalar_type x = 7.5324;
    assert(po::expr_rank(x) == 0);

    PO_LINE;
 }

  {
    po::polynomial p{{2, {1, 5, 4, 2, 0, 0, 1, 1}}};
    assert(po::expr_rank(p) == 8);

    PO_LINE;
 }

  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = D(p, 0);
    assert(po::expr_rank(x) == 3);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 5, 4, 2, 0, 0, 1, 1}}};
    auto x = -p;
    assert(po::expr_rank(x) == 8);

    PO_LINE;
}

  {
    po::polynomial p{{2, {1, 5, 4, 2, 0, 0, 1, 1}}};
    auto x = +p;
    assert(po::expr_rank(x) == 8);

    PO_LINE;
 }

  {
    po::polynomial p{{2, {1, 5, 4, 2, 0, 0, 1, 1}}};
    auto x = -+-+p;
    assert(po::expr_rank(x) == 8);

    PO_LINE;
 }

  {
    po::polynomial p{{2, {1, 5, 4, 2, 0, 0, 1, 1}}};
    auto x = p+5;
    assert(po::expr_rank(x) == 8);

    PO_LINE;
 }

  {
    po::polynomial p{{2, {1, 5, 4, 0, 0, 1, 1}}};
    auto x = 5+p;
    assert(po::expr_rank(x) == 7);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 5, 4, 2, 0, 0, 1, 1}}};
    auto x = 2*p;
    assert(po::expr_rank(x) == 8);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 5, 1, 1}}};
    auto x = 2*p - p;
    assert(po::expr_rank(x) == 4);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 5, 1, 1}}};
    auto x = 3*p*p - 1;
    assert(po::expr_rank(x) == 4);

    PO_LINE;
  }

  // Antiderivative, place in range
  {
    po::polynomial p{{2, {1, 5, 1, 1}}};
    auto x = integral(3*p*p, {2, {-1, 1}}) - 1;
    assert(po::expr_rank(x) == 3);

    PO_LINE;
  }

  // Antiderivative, place OOR
  {
    po::polynomial p{{2, {1, 5, 1, 1}}};
    auto x = integral(3*p*p, {7, {-2, -2}}) - 1;
    PO_ASSERT(expr_rank(x) == 4, expr_rank(x));

    PO_LINE;
  }

  // Antiderivative, place in range
  {
    po::polynomial p{{2, {1, 5, 1, 1}}};
    auto x = D(3*p*p, 1) - 1;
    assert(po::expr_rank(x) == 4);

    PO_LINE;
  }

  // Antiderivative, place OOR
  {
    po::polynomial p{{2, {1, 5, 1, 1}}};
    auto x = D(3*p*p, 7) - 1;
    assert(po::expr_rank(x) == 4);

    PO_LINE;
  }

  // Antiderivative, place in range
  {
    po::polynomial p{{2, {1, 5, 1, 1}}};
    auto x = antiderivative(3*p*p, 1) - 1;
    assert(po::expr_rank(x) == 4);

    PO_LINE;
  }

  // Antiderivative, place OOR
  {
    po::polynomial p{{2, {1, 5, 1, 1}}};
    auto x = antiderivative(3*p*p, 5) - 1;
    assert(po::expr_rank(x) == 4);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 5, 1, 1, 7}}}, q{{5.5, {9, 8, 9, 8, 6}}, {1.2, {0, 1, 2, 0, 4}}};
    auto x = 2*p*(p - q) - D(q*D(3*p*p - q*q*p, 3), 4);
    assert(po::expr_rank(x) == 5);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 5, 1, 1, 7}}}, q{{5.5, {9,8,9,8,6}}, {1.2, {0, 1, 2, 0, 4}}};
    auto x = 2*p*(p - q) - D(q*D(3*p*p - q*q*p, 3), 4);
    po::polynomial ip(po::polynomial::make_zero(22));
    ip = x;
    assert(po::expr_rank(x) == 5);
    assert(ip.rank() == 5);

    PO_LINE;
  }

  {
    po::polynomial p{{  2, {1, 5, 1, 1, 7}}};
    po::polynomial q{{5.5, {9, 8, 9, 8, 6}}, {1.2, {0, 1, 2, 0, 4}}};
    po::polynomial r{{  2, {4, 3, 3, 3, 1, 6}}};
    auto x = 2*p*(p - q) + po::integral(r, {2, {0, 1}})- (q*D(3*p*p - q*q*p, 3), 4);
    po::polynomial ip(po::polynomial::make_zero(22));
    ip = x;
    assert(po::expr_rank(x) == 5);
    assert(ip.rank() == 5);

    PO_LINE;
  }

  {
    po::polynomial p{{  2, {1, 5, 1, 1, 7}}};
    po::polynomial q{{5.5, {9, 8, 9, 8, 6}}, {1.2, {0, 1, 2, 0, 4}}};

    assert(po::expr_rank(p*q) == 5);
    assert(po::expr_rank(integral(p*q, {2, {-1, 3}})) == 4);

    PO_LINE;
  }

  {
    po::polynomial p{{  2, {1, 5, 1, 1, 7}}};
    po::polynomial q{{5.5, {9, 8, 9, 8, 6}}, {1.2, {0, 1, 2, 0, 4}}};

    assert(po::expr_rank(p*q) == 5);
    assert(po::expr_rank(integral(p*q, {11, {-1, 3}})) == 5);

    PO_LINE;
  }

  // exprs with compatible rank
  {
    po::polynomial p{{  2, {1, 5, 1, 1, 7}}};
    po::polynomial q{{5.5, {9, 8, 9, 8, 6}}, {1.2, {0, 1, 2, 0, 4}}};

    assert(po::ranks_compatible(5, 6.2)); // (The grammar impl prevents this case.)
    assert(po::ranks_compatible(5, q));
    assert(po::ranks_compatible(p, 5));
    assert(po::ranks_compatible(p, q));
    assert(po::ranks_compatible(p, q + 6));
    assert(po::ranks_compatible(p, q*(q + 3)));
    assert(po::ranks_compatible(2*p, q*(q + 3)));
    assert(po::ranks_compatible(2*p - 8, 7));

    PO_LINE;
  }

  // exprs with incompatible rank
  {
    po::polynomial p{{  2, {1, 5, 1, 1, 7}}};
    po::polynomial q{{5.5, {9, 8, 9, 8, 6, 5}}, {1.2, {0, 1, 2, 0, 4, 0}}};

    assert(po::ranks_compatible(5, q));
    assert(po::ranks_compatible(p, 5));
    assert(!po::ranks_compatible(p, q));
    assert(!po::ranks_compatible(p, q + 6));
    assert(!po::ranks_compatible(p, q*(q + 3)));
    assert(!po::ranks_compatible(2*p, q*(q + 3)));

    PO_LINE;
  }

}




