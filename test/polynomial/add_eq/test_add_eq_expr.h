#include "test_add_eq_nullary_expr_level_0.h"
#include "test_add_eq_binary_expr_level_1.h"
#include "test_add_eq_binary_expr_level_2.h"
#include "test_add_eq_binary_expr_level_3.h"
#include "test_add_eq_binary_expr_level_4.h"
#include "test_add_eq_unary_plus_level_5.h"
#include "test_add_eq_unary_minus_level_5.h"

void test_add_eq_expr()
{
  test_add_eq_nullary_expr_level_0();
  test_add_eq_binary_expr_level_1();
  test_add_eq_binary_expr_level_2();
  test_add_eq_binary_expr_level_3();
  test_add_eq_binary_expr_level_4();
  test_add_eq_unary_plus_level_5();
  test_add_eq_unary_minus_level_5();
}

