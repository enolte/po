#include "test_evaluate_p__plus__c.h"
#include "test_evaluate_p__plus__p.h"
#include "test_evaluate_c__plus__p.h"

void test_evaluate_bplus__level_1()
{
  test_evaluate_p__plus__c();
  test_evaluate_p__plus__p();
  test_evaluate_c__plus__p();
}
