#include "expr_nullary_constant_evaluate/test_evaluate_expr_nullary_constant.h"
#include "expr_unary_plus_evaluate/test_evaluate_expr_unary_plus.h"
#include "expr_unary_minus_evaluate/test_evaluate_expr_unary_minus.h"
#include "expr_binary_plus_evaluate/test_evaluate_expr_binary_plus.h"
#include "expr_binary_minus_evaluate/test_evaluate_expr_binary_minus.h"
#include "expr_binary_mult_evaluate/test_evaluate_expr_binary_mult.h"
#include "expr_unary_derivative_evaluate/test_evaluate_expr_partial_derivative.h"
#include "expr_unary_integral_evaluate/test_evaluate_expr_integral.h"

void test_expr_evaluate()
{
  test_evaluate_expr_nullary_constant();
  test_evaluate_expr_unary_plus();
  test_evaluate_expr_unary_minus();
  test_evaluate_expr_binary_plus();
  test_evaluate_expr_binary_minus();
  test_evaluate_expr_binary_mult();
  test_evaluate_expr_partial_derivative();
  test_evaluate_expr_integral();
}