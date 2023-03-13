#include "test_evaluate_I__c_plus_p.h"
#include "test_evaluate_I__p_plus_c.h"
#include "test_evaluate_I__p_plus_p.h"
#include "test_evaluate_I__p_minus_p.h"
#include "test_evaluate_I__p_mult_p.h"
#include "test_evaluate_I__p_mult_c.h"
#include "test_evaluate_I__unary_plus_p.h"
#include "test_evaluate_I__unary_minus_p.h"
#include "test_evaluate_I__Dp.h"

void test_evaluate_I__level_1()
{
  test_evaluate_I__Dp();
  test_evaluate_I__c_plus_p();
  test_evaluate_I__p_plus_c();
  test_evaluate_I__p_plus_p();
  test_evaluate_I__p_minus_p();
  test_evaluate_I__p_mult_p();
  test_evaluate_I__p_mult_c();
  test_evaluate_I__unary_plus_p();
  test_evaluate_I__unary_minus_p();
}