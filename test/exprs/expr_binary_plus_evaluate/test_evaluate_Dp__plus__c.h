#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_Dp__plus__c()
{
  {
    po::polynomial p{{1, {3}}};
    assert((D(p, 0) - 7)(1) == -4);
  }

  {
    assert((D(po::polynomial{{1, {3}}}, 0) + 2)(1) == 5);
  }

  PO_LINE;
}
