#include "expr_unary_derivative_instantiate/test_instantiate_level_3.h"
#include "expr_binary_minus_instantiate/test_instantiate_level_3.h"
#include "expr_binary_mult_instantiate/test_instantiate_level_3.h"
#include "expr_binary_plus_instantiate/test_instantiate_level_3.h"

void test_instantiate_level_3()
{
  expr_unary_derivative_instantiate::test_instantiate_level_3();
  expr_binary_minus_instantiate::test_instantiate_level_3();
  expr_binary_mult_instantiate::test_instantiate_level_3();
  expr_binary_plus_instantiate::test_instantiate_level_3();
}
