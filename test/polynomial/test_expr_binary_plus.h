#include "test_expr_binary_plus_subexpressions.h"
#include "test_expr_binary_plus_evaluate.h"

void test_expr_binary_plus()
{
  test_expr_binary_plus_subexpressions();
  test_expr_binary_plus_evaluate();

  PO_LINE;
}
