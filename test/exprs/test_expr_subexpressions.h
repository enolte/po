#include "subexpressions/test_expr_nullary_constant_subexpression.h"
#include "subexpressions/test_expr_binary_minus_subexpressions.h"
#include "subexpressions/test_expr_binary_mult_subexpressions.h"
#include "subexpressions/test_expr_binary_plus_subexpressions.h"
#include "subexpressions/test_expr_unary_plus_subexpressions.h"
#include "subexpressions/test_expr_unary_minus_subexpressions.h"
#include "subexpressions/test_expr_unary_partial_derivative_subexpressions.h"
#include "subexpressions/test_expr_unary_integral_subexpressions.h"
#include "subexpressions/test_expr_unary_antiderivative_subexpressions.h"
// TODO
// #include "subexpressions/test_expr_unary_extend_subexpressions.h"

void test_expr_subexpressions()
{
  test_expr_nullary_constant_subexpression();
  test_expr_binary_minus_subexpressions();
  test_expr_binary_mult_subexpressions();
  test_expr_binary_plus_subexpressions();
  test_expr_unary_plus_subexpressions();
  test_expr_unary_minus_subexpressions();
  test_expr_unary_partial_derivative_subexpressions();
  test_expr_unary_integral_subexpressions();
  test_expr_unary_antiderivative_subexpressions();
//  test_expr_unary_extend_subexpressions();
}