#include "test_expr_binary_minus_subexpressions.h"
#include "test_expr_binary_minus_evaluate.h"

void test_expr_binary_minus()
{
  test_expr_binary_minus_subexpressions();
  test_expr_binary_minus_evaluate();

  PO_LINE;
}
