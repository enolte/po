#include "test_evaluate_c__plus__Dp.h"
#include "test_evaluate_Dc__plus__p.h"
#include "test_evaluate_p__plus__Dp.h"
#include "test_evaluate_Dp__plus__c.h"
#include "test_evaluate_Dp__plus__p.h"

void test_evaluate_bplus__level_2()
{
  test_evaluate_c__plus__Dp();
  test_evaluate_Dc__plus__p();
  test_evaluate_p__plus__Dp();
  test_evaluate_Dp__plus__c();
  test_evaluate_Dp__plus__p();
}
