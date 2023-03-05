#include "../../ostream/valarray_ostream.h"

#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_expr_integral__unary_plus_p_evaluate()
{
  // l-value p
  {
    po::polynomial p{{ 2, {1, 1, 1, 1}}};

    const double ex = 48;

    const double ac = po::integral(+p, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
  }

  {
    const po::polynomial p
    {
      { 2  , {1, 1, 1, 1}},
      { 0.4, {7, 1, 0, 3}},
    };

    const double ex = 3547.2;
    const double ac = po::integral(+p, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(po_test::near_rel(ac, ex, 0x1p-51), po_test::errors(ac, ex, 0x1p-51));
  }

  // r-value p
  {
    const double ex = 5149.5733333333;

    const double ac = po::integral(
      +po::polynomial
      {
        { 2     , {1, 1, 1, 1}},
        { 0.0003, {5, 5, 8, 3}},
      },
      {2, {1, 3}})
        (3, 2, 1);

    PO_ASSERT(po_test::near_rel(ac, ex, 0x1.cp-23), po_test::errors(ac, ex, 0x1.cp-23));
  }

  PO_LINE;
}
