#include "test_evaluate_bplus__level_1.h"
#include "test_evaluate_bplus__level_2.h"
#include "test_evaluate_bplus__level_3.h"

void test_evaluate_bplus();

void test_evaluate_expr_binary_plus()
{
  test_evaluate_bplus();
}

void test_evaluate_bplus()
{
  test_evaluate_bplus__level_1();
  test_evaluate_bplus__level_2();
  test_evaluate_bplus__level_3();
}