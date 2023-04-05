#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_evaluate_A__p_mult_c()
{
  // l-value p, l-value c
  {
    po::polynomial p           {{ 2, {1, 1, 1, 1}}};
    const double c = -1.7;
    const double ex = -1.7 * 3 * 2 * 3*3 * 1;
    const double ac = po::antiderivative(p * c, 2)(3, 2, 3, 1);

    PO_ASSERT(ac == ex, ac);

    PO_LINE;
  }

  // r-value p, r-value c
  {
    po::polynomial p           {{ 2, {1, 1, 1, 1}}};

    const double ex = -1.7 * 3 * 2 * 3*3 * 1;
    const double ac = po::antiderivative(po::polynomial{{ 2, {1, 1, 1, 1}}} * -1.7, 2)(3, 2, 3, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == -91.8, ac);

    PO_LINE;
  }

}
