#include "test_evaluate_D__level_0.h"
#include "test_evaluate_D__level_1.h"
#include "test_evaluate_D__level_2.h"
#include "test_evaluate_D__level_3.h"

void test_evaluate_D();

void test_evaluate_expr_partial_derivative()
{
  test_evaluate_D();
}

void test_evaluate_D()
{
  test_evaluate_D__level_0();
  test_evaluate_D__level_1();
  test_evaluate_D__level_2();
  test_evaluate_D__level_3();
}


