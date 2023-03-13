#include "sub_eq/test_sub_eq_expr.h"
#include "sub_eq/test_sub_eq_init_list.h"
#include "sub_eq/test_sub_eq_monomial.h"
#include "sub_eq/test_sub_eq_scalar.h"
#include "sub_eq/test_sub_eq_polynomial.h"

void test_sub_eq()
{
  test_sub_eq_expr();
  test_sub_eq_init_list();
  test_sub_eq_monomial();
  test_sub_eq_scalar();
  test_sub_eq_polynomial();
}

