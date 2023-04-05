#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

#include "A.h"
#include "../expr_unary_integral_evaluate/I.h"

void test_evaluate_A__Ip()
{
  // lvalue polynomial, A-place in range, I-place in range
  {
    po::polynomial p{{ 2, {1, 0}}};

    const double ac = A(I(p, {0, {-1, 3}}), 0)(2.2);
    const double ex = 8 * 2.2;

    PO_ASSERT(ac == ex, "ac = " << ac << ", ex = " << ex);

    PO_LINE;
  }

  // lvalue polynomial, A-place in range, I-place in range, test 2
  {
    po::polynomial p{{ 2, {1, 0, 2, 1}}};

    const double ac = A(I(p, {0, {-1, 3}}), 0)(1.1, 2.2, 3.3);

    const double ex = 1.1 * 8 * 2.2*2.2 * 3.3;

    assert(po_test::near_rel(ac, ex, 0x1p-52));

    PO_LINE;
  }

}

