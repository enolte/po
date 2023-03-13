#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_p__mult__p()
{
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    assert((p*q)(4, 3, 3.4, 8) == p(4, 3, 3.4, 8) * q(4, 3, 3.4, 8));
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
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    const double left = (p*(q*q))(0.4, 3, 0.34, 8);
    const double right= p(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8);

    PO_ASSERT(
      po_test::near_rel(left, right, 0x1p-52),
      po_test::errors(left, right, 0x1p-52));
  }

  {
    const po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    const po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    const double left = (p*(q*q))(0.4, 3, 0.34, 8);
    const double right= p(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8) * q(0.4, 3, 0.34, 8);

    PO_ASSERT(
      po_test::near_rel(left, right, 0x1p-52),
      po_test::errors(left, right, 0x1p-52));
  }

  PO_LINE;
}
