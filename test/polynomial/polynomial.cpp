#include <cassert>
#include <iostream>
#include <iomanip>

#include "../../polynomial.h"

#include "../../test/macros.h"
#include "../../ostream/vector_ostream.h"
#include "../../ostream/monomial_ostream.h"
#include "../../ostream/polynomial_ostream.h"

#include "test_scalar_field.h"

#include "test_ctor_exprs.h"
#include "test_assignment.h"
#include "test_ctor_constant_term_initialization.h"
#include "test_ctor_variable_degrees_initialization.h"
#include "test_ctor_rank_initialization.h"
#include "test_ctor_terms_initialization.h"
#include "test_coefficient.h"
#include "test_degree.h"
#include "test_evaluate.h"
#include "test_add_eq_monomial.h"
#include "test_add_eq_scalar.h"
#include "test_sub_eq_monomial.h"
#include "test_mult_eq_monomial.h"
#include "test_mult_eq_scalar.h"
#include "test_mult_eq_polynomial.h"
// #include "test_expr.h"
#include "test_expr_constant.h"
#include "test_is_binary_expression.h"
#include "test_is_unary_expression.h"
#include "test_is_expression.h"
#include "test_expr_unary_plus.h"
#include "test_expr_unary_minus.h"
#include "test_expr_binary_plus.h"
#include "test_expr_binary_minus.h"
#include "test_expr_binary_mult.h"
#include "test_expr_partial_derivative.h"
#include "test_instantiate.h"

void test();

int main()
{
  test();

  return 0;
}

void test()
{
  test_scalar_field();
  test_ctor_exprs();
  test_ctor_rank_initialization();
  test_ctor_constant_term_initialization();
  test_ctor_variable_degrees_initialization();
  test_ctor_terms_initialization();
  test_assignment();
  test_coefficient();
  test_degree();
  test_evaluate();
  test_add_eq_monomial();
  test_add_eq_scalar();
  test_sub_eq_monomial();
  test_mult_eq_scalar();
  test_mult_eq_monomial();
  test_mult_eq_polynomial();
  // test_expr();
  test_expr_constant();
  test_is_binary_expression();
  test_is_unary_expression();
  test_is_expression();
  test_expr_unary_plus();
  test_expr_unary_minus();
  test_expr_binary_plus();
  test_expr_binary_minus();
  test_expr_binary_mult();
  test_expr_partial_derivative();
  test_instantiate();
}




