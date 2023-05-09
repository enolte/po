#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_p__plus__p__different_ranks();

void test_evaluate_p__plus__p()
{
  {
    po::polynomial p{{1, {0, 1, 3}}, {3.2, {2, 0, 0}}}, q{{3, {4, 3, 1}}};

    assert((p + q)(4, 3, 2 == p(4, 3, 2) + q(4, 3, 2)));

    PO_LINE;
  }

  // same rank
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {1, 4, 2, 3}}, {1, {0, 0, 0, 0}}};

    const double ex = (p+(q - 6))(4, 3, 3.4, 8);
    const double ep = p(4, 3, 3.4, 8);
    const double eq = q(4, 3, 3.4, 8);

    assert(eq == eq);
    assert(ep == ep);
    assert(ex == ex);

    PO_LINE;
  }

  test_evaluate_p__plus__p__different_ranks();
}

void test_evaluate_p__plus__p__different_ranks()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {1, 4, 2}}, {1, {0, 0, 0}}};

    const double epq = (p+q)(4, 3, 3.4, 8);
    const double ep = p(4, 3, 3.4, 8);
    const double eq = q(4, 3, 3.4, 8);

    assert(eq != eq);
    assert(ep == ep);
    assert(epq != epq);

    PO_LINE;
  }

  // different rank
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {1, 4, 2}}, {1, {0, 0, 0}}};

    const double ex = (p+(q - 6))(4, 3, 3.4, 8);
    const double ep = p(4, 3, 3.4, 8);
    const double eq = q(4, 3, 3.4, 8);

    assert(eq != eq);
    assert(ep == ep);
    assert(ex != ex);

    PO_LINE;
  }
}