#include "../../../ostream/valarray_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_evaluate_I__p_plus_c()
{
  // l-value constant, l-value polynomial
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};

    const double c = 0.;

    const double ex = c + po::integral(p, {2, {1, 3}})(3, 2, 1);
    const double ac = po::integral(p + c, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 0. + 48, ac);
  }

  // r-value constant, l-value polynomial
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};

    const auto ex = 10.4 + po::integral(p, {2, {1, 3}})(3, 2, 1);
    const auto ac = po::integral(p + 5.2, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 10.4 + 48, ac);
  }

  // l-value constant, r-value polynomial
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};

    const double c = 5.2;

    const auto ex = 10.4 + po::integral(p, {2, {1, 3}})(3, 2, 1);
    const auto ac = po::integral(po::polynomial{{2, {1, 1, 1, 1}}} + c, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 10.4 + 48, ac);
  }

  // r-value constant, r-value polynomial
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};

    const auto ex = 10.4 + po::integral(p, {2, {1, 3}})(3, 2, 1);
    const auto ac = po::integral(po::polynomial{{2, {1, 1, 1, 1}}} + 5.2, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 10.4 + 48, ac);
  }

  PO_LINE;
}
