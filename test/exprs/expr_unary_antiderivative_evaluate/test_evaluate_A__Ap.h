#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

#include "A.h"

void test_evaluate_A__Ap()
{
  // lvalue polynomial, outer A-place in range, inner A-place in range
  {
    po::polynomial p{{ 2, {1, 0}}};

    const double ex = 2.2*2.2 * 3.74;
    const double ac = A(A(p, 1), 0)(2.2, 3.74);

    PO_ASSERT(ac == ex, "ac = " << ac << ", ex = " << ex);

    PO_LINE;
  }

  // lvalue polynomial, outer A-place in range, inner A-place in range, test 2
  {
    po::polynomial p{{ 2, {1, 0, 2, 1}}};

    const double ex = 1./3 * 1.331 * 4.84 * 3.3;
    const double ac = A(A(p, 0), 0)(1.1, -5, 2.2, 3.3);

    PO_ASSERT(po_test::near_rel(ac, ex, 0x1.8p-51), po_test::errors(ac, ex));

    PO_LINE;
  }

  // lvalue polynomial, outer A-place OOR, inner A-place in range, test 2
  {
    po::polynomial p{{ 2, {1, 0, 2, 1}}};

    const double ex = 1.21 * 4.84 * 3.3 * 4.2;
    const double ac = A(A(p, 0), 5)(1.1, -5, 2.2, 3.3, 0, 4.2);

    PO_ASSERT(po_test::near_rel(ac, ex, 0x1p-51), po_test::errors(ac, ex));

    PO_LINE;
  }

}

