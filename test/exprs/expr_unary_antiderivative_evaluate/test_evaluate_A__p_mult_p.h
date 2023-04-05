#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_evaluate_A__p_mult_p()
{
  // l-value p, l-value q
  {
    po::polynomial p           {{ 2, {1, 1, 1, 1}}};
    po::polynomial q           {{ 7, {1, 0, 2, 5}}};
/*
    pq = {14, {2, 1, 3, 6}}

    A(pq, 2) = {14/4, {2, 1, 4, 6}}
*/
    const double ex = 14./4 * 3*3 * 2 * 3*3*3*3 * 1;
    const double ac = po::antiderivative(p * q, 2)(3, 2, 3, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 5103., ac);

    PO_LINE;
  }

  // r-value p, r-value q
  {
/*
    Expect same result, using the usual chain rule.
*/
    po::polynomial p           {{ 2, {1, 1, 1, 1}}};
    po::polynomial P2          {{ 1, {1, 1, 2, 1}}}; // antiderivative(p) in place 2
    po::polynomial q           {{ 7, {1, 0, 2, 5}}};
    po::polynomial q2          {{14, {1, 0, 1, 5}}}; // dq/dx2

    const double ex =
      P2(3, 2, 3, 1) * q(3, 2, 3, 1)
      -
      po::antiderivative(P2 * q2, 2)(3, 2, 3, 1);

    const double ac = po::antiderivative(
      po::polynomial{{ 2, {1, 1, 1, 1}}} * po::polynomial{{ 7, {1, 0, 2, 5}}}, 2)(3, 2, 3, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 5103., ac);

    PO_LINE;
  }

}
