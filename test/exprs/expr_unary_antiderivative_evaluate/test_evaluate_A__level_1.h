#include "test_evaluate_A__p_minus_p.h"
#include "test_evaluate_A__p_plus_p.h"
#include "test_evaluate_A__p_mult_p.h"
#include "test_evaluate_A__p_mult_c.h"
#include "test_evaluate_A__unary_plus_p.h"
#include "test_evaluate_A__unary_minus_p.h"
#include "test_evaluate_A__Dp.h"
#include "test_evaluate_A__Ip.h"
#include "test_evaluate_A__Ap.h"

void test_evaluate_A__level_1()
{
  test_evaluate_A__p_minus_p();
  test_evaluate_A__p_plus_p();
  test_evaluate_A__p_mult_p();
  test_evaluate_A__p_mult_c();
  test_evaluate_A__unary_plus_p();
  test_evaluate_A__unary_minus_p();
  test_evaluate_A__Dp();
  test_evaluate_A__Ip();
  test_evaluate_A__Ap();
}

