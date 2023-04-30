#include "test_assign_expr_nullary_constant_level_0.h"
#include "test_assign_expr_unary_plus_level_1.h"
#include "test_assign_expr_unary_plus_level_5.h"
#include "test_assign_expr_unary_minus_level_1.h"
#include "test_assign_expr_unary_minus_level_7.h"
#include "test_assign_expr_binary_plus_level_1.h"
#include "test_assign_expr_binary_plus_level_3.h"
#include "test_assign_expr_binary_minus_level_1.h"
#include "test_assign_expr_level_4.h"
#include "test_assign_expr_level_6.h"

void test_assign_expr()
{
  test_assign_expr_nullary_constant_level_0();
  test_assign_expr_unary_plus_level_1();
  test_assign_expr_unary_plus_level_5();
  test_assign_expr_unary_minus_level_1();
  test_assign_expr_unary_minus_level_7();
  test_assign_expr_binary_plus_level_1();
  test_assign_expr_binary_plus_level_3();
  test_assign_expr_binary_minus_level_1();
  test_assign_expr_level_4();
  test_assign_expr_level_6();
}

