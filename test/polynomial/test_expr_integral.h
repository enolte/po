#include "test_expr_integral_c_evaluate.h"
#include "test_expr_integral_p_evaluate.h"
#include "test_expr_integral__c_plus_p_evaluate.h"
#include "test_expr_integral__p_plus_c_evaluate.h"
#include "test_expr_integral__p_plus_p_evaluate.h"
#include "test_expr_integral__p_minus_p_evaluate.h"
#include "test_expr_integral__p_mult_p_evaluate.h"
#include "test_expr_integral__p_mult_c_evaluate.h"
#include "test_expr_integral__unary_plus_p_evaluate.h"
#include "test_expr_integral__unary_minus_p_evaluate.h"

#include "test_expr_integral_Dp_evaluate.h"

void test_expr_integral()
{
  test_expr_integral_c_evaluate();
  test_expr_integral_p_evaluate();
  test_expr_integral_Dp_evaluate();
  test_expr_integral__c_plus_p_evaluate();
  test_expr_integral__p_plus_c_evaluate();
  test_expr_integral__p_plus_p_evaluate();
  test_expr_integral__p_minus_p_evaluate();
  test_expr_integral__p_mult_p_evaluate();
  test_expr_integral__p_mult_c_evaluate();
  test_expr_integral__unary_plus_p_evaluate();
  test_expr_integral__unary_minus_p_evaluate();

  PO_LINE;
}

