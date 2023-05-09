#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_p__mult__p__different_ranks();

void test_evaluate_p__mult__p()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert((p*q)(4, 3, 3.4, 8) == p(4, 3, 3.4, 8) * q(4, 3, 3.4, 8));

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert((p*q*q)(4, 3, 3.4, 8) == p(4, 3, 3.4, 8) * q(4, 3, 3.4, 8) * q(4, 3, 3.4, 8));

    const double left = (p*q*q)(0.4, 3, 0.34, 8);
    const double right= p(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8);

    PO_ASSERT(
      left == right,
      po_test::errors(left, right, 0x1p-52));

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert(((p*q)*q)(4, 3, 3.4, 8) == p(4, 3, 3.4, 8) * q(4, 3, 3.4, 8) * q(4, 3, 3.4, 8));

    const double left = ((p*q)*q)(0.4, 3, 0.34, 8);
    const double right= p(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8);

    PO_ASSERT(
      left == right,
      po_test::errors(left, right, 0x1p-52));

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    const double left = (p*(q*q))(0.4, 3, 0.34, 8);
    const double right= p(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8);

    PO_ASSERT(
      po_test::near_rel(left, right, 0x1p-52),
      po_test::errors(left, right, 0x1p-52));

    PO_LINE;
  }

  {
    const po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    const po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    const double left = (p*(q*q))(0.4, 3, 0.34, 8);
    const double right= p(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8);

    PO_ASSERT(
      po_test::near_rel(left, right, 0x1p-52),
      po_test::errors(left, right, 0x1p-52));

    PO_LINE;
  }

  test_evaluate_p__mult__p__different_ranks();
}

void test_evaluate_p__mult__p__different_ranks()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {1, 4, 2}}, {1, {0, 0, 0}}};

    const double epq = (p*q)(4, 3, 3.4, 8);
    const double ep = p(4, 3, 3.4, 8);
    const double eq = q(4, 3, 3.4, 8);

    assert(eq != eq);
    assert(ep == ep);
    assert(epq != epq);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {1, 4, 2}}, {1, {0, 0, 0}}};

    const double ex = (p*(q - 6))(4, 3, 3.4, 8);
    const double ep = p(4, 3, 3.4, 8);
    const double eq = q(4, 3, 3.4, 8);

    assert(eq != eq);
    assert(ep == ep);
    assert(ex != ex);

    PO_LINE;
  }
}
