#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_evaluate_I__c()
{
  {
    const double ex = 18.5;
    const double ac = po::integral(1., {0, {0, 18.5}})();

    assert(ac == ex);

    PO_LINE;
  }

  {
    const double ex = 21.2;
    const double ac = po::integral(1., {1, {-11., 10.2}})();

    assert(ac == ex);

    PO_LINE;
  }

  {
    const double ex = 2.3 * 21.2;
    const double ac = po::integral(2.3, {2, {-11., 10.2}})();

    assert(ac == ex);

    PO_LINE;
  }
#if 0
  // TODO
  {
    const double ex = 2.3 * 21.2;
    const double ac = po::integral(1, {2, {-11., 10.2}})();

    assert(ac == ex);

    PO_LINE;
  }
#endif

}
