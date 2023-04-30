#include "concepts/test_is_scalar.h"
#include "concepts/test_is_constant.h"
#include "concepts/test_is_binary_expression.h"
#include "concepts/test_is_unary_expression.h"
#include "concepts/test_is_expression.h"
#include "concepts/test_is_subexpr_type.h"

void test_concepts()
{
  test_is_scalar();
  test_is_constant();
  test_is_binary_expression();
  test_is_unary_expression();
  test_is_expression();
  test_is_subexpr_type();
}