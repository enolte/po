#include "../../ostream/valarray_ostream.h"

#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_expr_integral__p_plus_p_evaluate()
{
  // l-value p, l-value q
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
    po::polynomial q           {{7, {1, 0, 0, 5}}};

    const double ex = po::integral(p, {2, {1, 3}})(3, 2, 1) + po::integral(q, {2, {1, 3}})(3, 2, 1);
    const double ac = po::integral(p + q, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 90., ac);
  }

  // l-value p, r-value q
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
    po::polynomial q           {{7, {1, 0, 0, 5}}};

    const double ex = po::integral(p, {2, {1, 3}})(3, 2, 1) + po::integral(q, {2, {1, 3}})(3, 2, 1);
    const double ac = po::integral(p + po::polynomial{{7, {1, 0, 0, 5}}}, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 90., ac);
  }

  // r-value p, l-value q
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
    po::polynomial q           {{7, {1, 0, 0, 5}}};

    const double ex = po::integral(p, {2, {1, 3}})(3, 2, 1) + po::integral(q, {2, {1, 3}})(3, 2, 1);
    const double ac = po::integral(po::polynomial{{2, {1, 1, 1, 1}}} + q, {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 90., ac);
  }

  // r-value p, r-value q
  {
    po::polynomial p           {{2, {1, 1, 1, 1}}};
    po::polynomial q           {{7, {1, 0, 0, 5}}};

    const double ex = po::integral(p, {2, {1, 3}})(3, 2, 1) + po::integral(q, {2, {1, 3}})(3, 2, 1);
    const double ac = po::integral(
      po::polynomial{{2, {1, 1, 1, 1}}} + po::polynomial{{7, {1, 0, 0, 5}}},
      {2, {1, 3}})(3, 2, 1);

    PO_ASSERT(ac == ex, ac);
    PO_ASSERT(ac == 90., ac);
  }

  PO_LINE;
}
