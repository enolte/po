#include "test_evaluate_extend_p.h"
#include "test_evaluate_extend_c.h"
#include "test_evaluate_mult.h"
// TODO
// #include "test_evaluate_extend_binary_plus.h"

void test_evaluate_expr_extend()
{
  test_evaluate_extend_p();
  test_evaluate_extend_c();
  test_evaluate_mult();
  // test_evaluate_extend_binary_plus();
}
