#include "test_evaluate_D__p_plus_p.h"
#include "test_evaluate_D__c_plus_p.h"
#include "test_evaluate_D__p_plus_c.h"
#include "test_evaluate_D__Dp.h"
#include "test_evaluate_D__Ip.h"

void test_evaluate_D__level_1()
{
  test_evaluate_D__p_plus_p();
  test_evaluate_D__c_plus_p();
  test_evaluate_D__p_plus_c();
  test_evaluate_D__Dp();
  test_evaluate_D__Ip();
}