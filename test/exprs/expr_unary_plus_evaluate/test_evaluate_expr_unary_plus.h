#include "test_evaluate_uplus__level_0.h"
#include "test_evaluate_uplus__level_1.h"
#include "test_evaluate_uplus__level_2.h"

void test_evaluate_uplus();

void test_evaluate_expr_unary_plus()
{
  test_evaluate_uplus();
}

void test_evaluate_uplus()
{
  test_evaluate_uplus__level_0();
  test_evaluate_uplus__level_1();
  test_evaluate_uplus__level_2();
}