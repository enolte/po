#include "test_expr_integral_c_evaluate.h"
#include "test_expr_integral_p_evaluate.h"
#include "test_expr_integral_Dp_evaluate.h"

void test_expr_integral()
{
  test_expr_integral_c_evaluate();
  test_expr_integral_p_evaluate();
  test_expr_integral_Dp_evaluate();

  PO_LINE;
}

