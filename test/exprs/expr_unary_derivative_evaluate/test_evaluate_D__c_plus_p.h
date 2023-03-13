#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_D__c_plus_p()
{
  // r-value + l-value
  {
    po::polynomial p{{1, {3}}};
    assert(D(4 + p, 0)(1) == 3);
    assert(D(4 + p, 0)(2) == 12);
  }

  // r-value + r-value
  {
    assert(D(4 + po::polynomial{{1, {3}}}, 0)(1) == 3);
    assert(D(4 + po::polynomial{{1, {3}}}, 0)(2) == 12);
  }

  PO_LINE;
}
