#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_evaluate_A__unary_plus_p()
{
  // l-value p. test 1
  {
    po::polynomial p{{ 2, {1, 1, 1, 1}}};

    const double ex = 3 * 2 * 4*4 * 1;
    const double ac = po::antiderivative(+p, 2)(3, 2, 4, 1);

    PO_ASSERT(ac == ex, ac);

    PO_LINE;
  }

  // l-value p, test 2
  {
    const po::polynomial p
    {
      { 2  , {1, 1, 1, 1}},
      { 0.4, {7, 1, 0, 3}},
    };

    const double ex = 3 * 2 * 4*4 * 1  +  0.4 * 3*3*3*3*3*3*3 * 2 * 4 * 1;
    const double ac = po::antiderivative(+p, 2)(3, 2, 4, 1);

    PO_ASSERT(ac == ex, po_test::errors(ac, ex, 0x1p-51));

    PO_LINE;
  }

  // r-value p
  {
    const double ex = 3 * 2 * 4*4 * 1  +  0.0003 / 9 * 3*3*3*3*3 * 2*2*2*2*2 * 4*4*4*4*4*4*4*4*4 * 1;
    const double ac = po::antiderivative(
      +po::polynomial
      {
        { 2     , {1, 1, 1, 1}},
        { 0.0003, {5, 5, 8, 3}},
      }, 2)
      (3, 2, 4, 1);

    PO_ASSERT(ac == ex, po_test::errors(ac, ex, 0x1p-51));
    PO_ASSERT(ac == 0x1.09cbb98c7e282p+16, po_test::errors(ac, ex, 0x1p-51, 20));
    // PO_ASSERT(ac == 68043.7, po_test::errors(ac, ex, 0x1p-51));

    PO_LINE;
  }

}
