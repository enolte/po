#include "expr_unary_plus_instantiate/test_instantiate_level_2.h"
#include "expr_unary_minus_instantiate/test_instantiate_level_2.h"
#include "expr_unary_derivative_instantiate/test_instantiate_level_2.h"
#include "expr_unary_integral_instantiate/test_instantiate_level_2.h"
#include "expr_binary_minus_instantiate/test_instantiate_level_2.h"
#include "expr_binary_mult_instantiate/test_instantiate_level_2.h"
#include "expr_binary_plus_instantiate/test_instantiate_level_2.h"

void test_instantiate_level_2()
{
  expr_unary_plus_instantiate::test_instantiate_level_2();
  expr_unary_minus_instantiate::test_instantiate_level_2();
  expr_unary_derivative_instantiate::test_instantiate_level_2();
  expr_unary_integral_instantiate::test_instantiate_level_2();
  expr_binary_minus_instantiate::test_instantiate_level_2();
  expr_binary_mult_instantiate::test_instantiate_level_2();
  expr_binary_plus_instantiate::test_instantiate_level_2();
}

