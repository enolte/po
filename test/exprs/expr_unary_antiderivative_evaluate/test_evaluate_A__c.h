#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_evaluate_A__c()
{
  // rvalue scalar field member
  {
    const double ex = 3.0058;
    const double ac = po::antiderivative(1., 0)(3.0058);

    assert(ac == ex);

    PO_LINE;
  }

  // rvalue scalar field member, nan arg --> nan result
  {
    const double ac = po::antiderivative(po::nan, 0)(3.0058);

    assert(ac != ac);

    PO_LINE;
  }


  // lvalue scalar field member
  {
    const double c = 9.0234;
    const double ex = 9.0234*3.0058;
    const double ac = po::antiderivative(c, 0)(3.0058);

    assert(ac == ex);

    PO_LINE;
  }

  //rvalue expr_constant
  {
    const double ex = -4.3*3.0058;
    const double ac = po::antiderivative(po::expr_constant{-4.3}, 0)(3.0058);

    assert(ac == ex);

    PO_LINE;
  }

  //lvalue expr_constant
  {
    po::expr_constant c{-4.3};
    const double ex = -4.3*3.0058;
    const double ac = po::antiderivative(c, 0)(3.0058);

    assert(ac == ex);

    PO_LINE;
  }

  // rvalue scalar field member, rank > 1, nan arg
  {
    const double ac = po::antiderivative(1., 2)(1, po::nan, 3.0058);

    assert(ac != ac);

    PO_LINE;
  }

  // rvalue scalar field member, rank > 1, no nans
  {
    const double ex = 3.0058;
    const double ac = po::antiderivative(1., 2)(1, -0.8, 3.0058);

    assert(ac == ex);

    PO_LINE;
  }

}
