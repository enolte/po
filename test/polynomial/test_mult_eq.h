#include "mult_eq/test_mult_eq_expr.h"
#include "mult_eq/test_mult_eq_init_list.h"
#include "mult_eq/test_mult_eq_monomial.h"
#include "mult_eq/test_mult_eq_scalar.h"
#include "mult_eq/test_mult_eq_polynomial.h"

void test_mult_eq()
{
  test_mult_eq_expr();
  test_mult_eq_init_list();
  test_mult_eq_monomial();
  test_mult_eq_scalar();
  test_mult_eq_polynomial();
}

