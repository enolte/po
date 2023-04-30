#include "../../../ops/is_unary_expression.h"
#include "../../../ops/expr_constant.h"
#include "../../../ops/is_constant.h"
#include "../../../types/scalar.h"

void test_is_constant()
{
  PO_LINE;
}

namespace static_asserts
{
  static_assert(po::is_unary_expression<po::expr_constant>);
  static_assert(po::is_constant<po::expr_constant>);
  static_assert(po::is_constant<po::scalar_type>);

  static_assert(po::is_constant<int>);
  static_assert(po::is_constant<long>);
  static_assert(po::is_constant<long long>);
  static_assert(po::is_constant<double>);
  static_assert(po::is_constant<float>);

}

