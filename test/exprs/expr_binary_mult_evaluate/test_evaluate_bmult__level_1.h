#include "test_evaluate_p__mult__p.h"
#include "test_evaluate_c__mult__p.h"
#include "test_evaluate_p__mult__c.h"

void test_evaluate_bmult__level_1()
{
  test_evaluate_p__mult__p();
  test_evaluate_c__mult__p();
  test_evaluate_p__mult__c();
}