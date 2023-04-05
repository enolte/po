#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../macros.h"
#include <cassert>

#include "A.h"

void test_evaluate_A__Dp()
{
  // lvalue polynomial, A-place == D-place, in range
  {
    po::polynomial p{{ 1, {1, 0}}};

    const double ac = A(D(p, 0), 0)(7, 2.2);
    const double ex = p(7, 2.2);

    assert(ac == ex);
    PO_LINE;
  }

  // lvalue polynomial, A-place == D-place, in range
  {
    po::polynomial p{{ 2, {1, 0}}};

    const double ac = A(D(p, 0), 0)(7, 2.2);
    const double ex = p(7, 2.2);
    assert(ac == ex);

    PO_LINE;
  }

  // lvalue polynomial, A-place in range, D-place in range
  {
    po::polynomial p{{ 2, {1, 0}}};

    const double ac = A(D(p, 0), 0)(7, 2.2);
    const double ex = 2*7.;
    assert(ac == ex);

    PO_LINE;
  }

  // rvalue polynomial, A-place in range, D-place in range
  {
    const double ac = A(D(po::polynomial{{ 2, {1, 0}}}, 0), 0)(7, 2.2);
    const double ex = 2*7.;

    assert(ac == ex);

    PO_LINE;
  }

  // lvalue polynomial, A-place OOR, D-place in range
  // rank-changing operation
  {
    po::polynomial p{{ 2, {1, 0}}};

    double ac = A(D(p, 0), 3)(7, 2.2);
    assert(ac != ac);

    ac = A(D(p, 0), 3)(7, 2.2, 1, 5.6);
    const double ex = 2*5.6;

    assert(ac == ex);

    PO_LINE;
  }

  // lvalue polynomial, A-place in range, D-place OOR
  {
    po::polynomial p{{ 2, {1, 0}}};

    const double ac = A(D(p, 5), 1)(7, 2.2);
    const double ex = 0.;
    assert(ac == ex);

    PO_LINE;
  }


  // lvalue polynomial, A-place OOR , D-place OOR
  // rank-changing
  {
    po::polynomial p{{ 2, {1, 0}}};

    double ac = A(D(p, 5), 4)(7, 2.2);
    assert(ac != ac);

    ac = A(D(p, 5), 4)(7, 2.2, 1, 1, 3.1);
    const double ex = 0.;
    assert(ac == ex);

    PO_LINE;
  }
}
