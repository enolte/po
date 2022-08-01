#include "../../ops/is_scalar.h"

void test_scalar_field()
{
  PO_LINE;
}

namespace static_asserts
{
  static_assert(po::is_scalar<po::default_numeric_type>);

  static_assert(po::is_scalar<po::scalar_field<double>::type>);
  static_assert(po::is_scalar<po::scalar_field<float>::type>);

  static_assert(po::is_scalar<int>);
  static_assert(po::is_scalar<long>);
  static_assert(po::is_scalar<long long>);
  static_assert(po::is_scalar<double>);
  static_assert(po::is_scalar<float>);

}

