#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_D__p_times_p_times_p()
{
  {
    po::polynomial p{{1, {3, 3}}}, q{{2, {2, 1}}};

    assert(
      po_test::near_rel(
        D(q*p*p, 0)(2, 4.3),
        q(2, 4.3)*2*p(2, 4.3)*D(p, 0)(2, 4.3) + D(q, 0)(2, 4.3)*p(2, 4.3)*p(2, 4.3),
        0x1p-52));

    PO_LINE;
  }
}
