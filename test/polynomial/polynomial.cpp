#include <cassert>
#include <iostream>
#include <iomanip>

#include "../../test/macros.h"
#include "../../polynomial.h"

#include "../../ostream/vector_ostream.h"
#include "../../ostream/monomial_ostream.h"
#include "../../ostream/polynomial_ostream.h"

using po::operator<<;

#include "test_scalar_field.h"
#include "test_ctor_exprs.h"
#include "test_assignment.h"
#include "test_ctor_constant_term_initialization.h"
#include "test_ctor_variable_degrees_initialization.h"
#include "test_ctor_rank_initialization.h"
#include "test_ctor_terms_initialization.h"
#include "test_coefficient.h"
#include "test_nterms.h"
#include "test_degree.h"
#include "test_evaluate.h"

#include "test_add_eq_scalar.h"
#include "test_add_eq_polynomial.h"
#include "test_add_eq_monomial.h"
#include "test_add_eq_init_list.h"
#include "test_add_eq_expr.h"

#include "test_sub_eq_scalar.h"
#include "test_sub_eq_polynomial.h"
#include "test_sub_eq_monomial.h"
#include "test_sub_eq_init_list.h"
#include "test_sub_eq_expr.h"

#include "test_mult_eq_scalar.h"
#include "test_mult_eq_polynomial.h"
#include "test_mult_eq_monomial.h"
#include "test_mult_eq_init_list.h"
#include "test_mult_eq_expr.h"

#include "test_constant_term.h"

// Disabled for test iteration
// #include "expr_binary_operands_verify_types.h"

#include "test_expr_rank.h"
#include "test_expr_field_type.h"
#include "test_is_expr_field_type.h"

#include "test_is_binary_expression.h"
#include "test_is_unary_expression.h"
#include "test_is_expression.h"
#include "test_expr_constant.h"
#include "test_expr_unary_plus.h"
#include "test_expr_unary_minus.h"
#include "test_expr_binary_plus.h"
#include "test_expr_binary_minus.h"
#include "test_expr_binary_mult.h"
#include "test_expr_partial_derivative.h"
#include "test_expr_integral.h"

#include "test_instantiate.h"

void test();

int main()
{
  test();

  // This explicit call writes to stdout the digest of tested expressions.
  // static_asserts::expr_binary_operands_verify_types();

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
  test_nterms();
  test_degree();
  test_evaluate();

  test_add_eq_scalar();
  test_add_eq_polynomial();
  test_add_eq_monomial();
  test_add_eq_init_list();
  test_add_eq_expr();

  test_sub_eq_scalar();
  test_sub_eq_polynomial();
  test_sub_eq_monomial();
  test_sub_eq_init_list();
  test_sub_eq_expr();

  test_mult_eq_scalar();
  test_mult_eq_polynomial();
  test_mult_eq_monomial();
  test_mult_eq_init_list();
  test_mult_eq_expr();

  test_constant_term();

  test_expr_rank();
  test_expr_field_type();
  test_is_expr_field_type();

  test_is_binary_expression();
  test_is_unary_expression();
  test_is_expression();

  test_expr_constant();
  test_expr_unary_plus();
  test_expr_unary_minus();
  test_expr_binary_plus();
  test_expr_binary_minus();
  test_expr_binary_mult();
  test_expr_partial_derivative();
  test_expr_integral();

  test_instantiate();

}




