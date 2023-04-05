#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_D__Ip()
{
  {
    po::polynomial     p{{2, {1, 1, 1, 1}}, { 3, {0, 4, 2, 0}}};
    // po::polynomial   a3p{{1, {1, 1, 1, 2}}, {6 , {0, 4, 2, 1}}}; // antiderivative(p) from in place 3
    po::polynomial   i3p{{3, {1, 1, 1,  }}, { 9, {0, 4, 2,  }}}; // integral(p) from -1 to 2 in place 3
    po::polynomial d2i3p{{3, {1, 1, 0,  }}, {18, {0, 4, 1,  }}}; // d(i2p)/dx2

    const double ex = d2i3p(1, 1, 1);
    const double ac = D(integral(p, {3, {-1, 2}}), 2)(1, 1, 1);

    assert(expr_rank(D(integral(p, {3, {-1, 2}}), 2)) == 3);

    PO_ASSERT(ac == ex, po_test::errors(ac, ex, 0x1p-52));

    PO_LINE;
  }
}
