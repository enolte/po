#include "../../../ops/expr_constant.h"

#include <concepts>

void test_expr_nullary_constant_subexpression()
{
  PO_LINE;
}

namespace static_asserts
{
  static_assert(po::is_constant<po::scalar_type>);
  static_assert(po::is_constant<po::expr_constant>);
  static_assert(po::is_unary_expression<po::expr_constant>);

  static_assert(std::same_as<decltype(po::expr_constant{{}}()), po::scalar_type>);
  static_assert(std::same_as<decltype(po::expr_constant{{}}.expr1), const po::scalar_type>);
}

