#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_evaluate_I__p_minus_p()
{
  // l-value p, l-value q
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
    po::polynomial q           {{7, {1, 0, 0, 5}}};

    const double ex = po::integral(p, {2, {1, 3}})(3, 2, 1) - po::integral(q, {2, {1, 3}})(3, 2, 1);
    const double ac = po::integral(p - q, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 6., ac);

    PO_LINE;
  }

  // l-value p, r-value q
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
    po::polynomial q           {{7, {1, 0, 0, 5}}};

    const double ex = po::integral(p, {2, {1, 3}})(3, 2, 1) - po::integral(q, {2, {1, 3}})(3, 2, 1);
    const double ac = po::integral(p - po::polynomial{{7, {1, 0, 0, 5}}}, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 6., ac);

    PO_LINE;
  }

  // r-value p, l-value q
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
    po::polynomial q           {{7, {1, 0, 0, 5}}};

    const double ex = po::integral(p, {2, {1, 3}})(3, 2, 1) - po::integral(q, {2, {1, 3}})(3, 2, 1);
    const double ac = po::integral(po::polynomial{{2, {1, 1, 1, 1}}} - q, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 6., ac);

    PO_LINE;
  }

  // r-value p, r-value q
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
    po::polynomial q           {{7, {1, 0, 0, 5}}};

    const double ex = po::integral(p, {2, {1, 3}})(3, 2, 1) - po::integral(q, {2, {1, 3}})(3, 2, 1);
    const double ac = po::integral(
      po::polynomial{{2, {1, 1, 1, 1}}} - po::polynomial{{7, {1, 0, 0, 5}}},
      {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 6., ac);

    PO_LINE;
  }

}
