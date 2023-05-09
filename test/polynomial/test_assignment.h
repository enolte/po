#include "assign/test_assign_expr.h"
#include "assign/test_assign_init_list.h"
#include "assign/test_assign_monomial.h"
#include "assign/test_assign_scalar.h"
#include "assign/test_assign_polynomial.h"

void test_assignment()
{
  test_assign_expr();
  test_assign_init_list();
  test_assign_monomial();
  test_assign_scalar();
  test_assign_polynomial();
}

