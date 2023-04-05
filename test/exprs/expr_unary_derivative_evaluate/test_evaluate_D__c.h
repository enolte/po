#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_D__c()
{
  {
    po::expr_partial_derivative dc = po::D(3.2, 0);
    assert(dc(9.01) == 0);

    PO_LINE;
  }

  {
    auto dc = po::D(3.2, 0);
    assert(dc(9.01) == 0);

    PO_LINE;
  }

  {
    const po::expr_constant c{4.3};
    po::expr_partial_derivative dc = po::D(c, 2);
    assert(dc(9.01) == 0);

    PO_LINE;
  }

  {
    po::expr_constant c{4.3};
    po::expr_partial_derivative dc = po::D(c, 2);
    assert(dc(9.01) == 0);

    PO_LINE;
  }

  {
    po::expr_partial_derivative dc = po::D(po::expr_constant{4.3}, 2);
    assert(dc(9.01) == 0);

    PO_LINE;
  }

  {
    assert(po::D(4.3, 2)(9.01) == 0);

    PO_LINE;
  }
#if 0
  // TODO
  {
    assert(po::D(4, 2)(9.01) == 0);

    PO_LINE;
  }
#endif

}