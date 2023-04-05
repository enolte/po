#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_Dp__plus__p()
{
  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = D(p, 0) + p;

    static_assert(std::same_as<
      decltype(x.expr1),
      const po::expr_partial_derivative<po::polynomial&>
    >);

    PO_LINE;
  }

  {
    po::polynomial p{{1, {3}}};
    po::polynomial q{{2, {2}}};
    assert(((+D(p, 0)) + q)(1) == 5);

    PO_LINE;
  }

  {
    po::polynomial q{{2, {2}}};
    assert(((+(D(po::polynomial{{1, {3}}}, 0))) + q)(1) == 5);

    PO_LINE;
  }

  {
    po::polynomial p{{1, {3}}};
    assert(((+D(p, 0)) + po::polynomial{{2, {2}}})(1) == 5);

    PO_LINE;
  }

  {
    assert(
      (
        (+D(po::polynomial{{1, {3}}}, 0))
        +
        po::polynomial{{2, {2}}}
      )(1) == 5);

    PO_LINE;
  }
}
