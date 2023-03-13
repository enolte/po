#include "../../../ostream/valarray_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_evaluate_I__p_mult_c()
{
  // l-value p, l-value c
  {
    po::polynomial p           {{ 2, {1, 1, 1, 1}}};
    const double c = -1.5;
/*
    A2(pc) = {-3/2, {1, 1, 2, 1}}

    I(p, 2, [1, 3]) = A2(p)(3) - A2(p)(1)
                    = {-12, {1, 1, 1}}

    I(p, 2, [1, 3])(3, 2, 1) = -12 * (3**1 * 2**1 * 1**1)
                             = -72
*/
    const double ex = -72;
    const double ac = po::integral(p * c, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
  }

  // r-value p, r-value c
  {
/*
    Expect same result, using the usual chain rule.
*/
    po::polynomial p           {{ 2, {1, 1, 1, 1}}};
    po::polynomial P2          {{ 1, {1, 1, 2, 1}}}; // antiderivative(p) in place 2
    po::polynomial q           {{ 7, {1, 0, 2, 5}}};
    po::polynomial q2          {{14, {1, 0, 1, 5}}}; // dq/dx2

    const double ex = -72.;

    const double ac = po::integral(
      po::polynomial{{ 2, {1, 1, 1, 1}}} * -1.5, {2, {1, 3}})
        (3, 2, 1);

    // std::cout << po_test::errors(ac, ex, 0x1p-52);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == -72., ac);
  }

  PO_LINE;
}
