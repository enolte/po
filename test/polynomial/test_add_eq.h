#include "add_eq/test_add_eq_expr.h"
#include "add_eq/test_add_eq_init_list.h"
#include "add_eq/test_add_eq_monomial.h"
#include "add_eq/test_add_eq_scalar.h"
#include "add_eq/test_add_eq_polynomial.h"

void test_add_eq()
{
  test_add_eq_expr();
  test_add_eq_init_list();
  test_add_eq_monomial();
  test_add_eq_scalar();
  test_add_eq_polynomial();
}

