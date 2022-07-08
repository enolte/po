#include "../../field.h"

void test_scalar_field()
{
  PO_LINE;
}


namespace static_asserts
{
  static_assert(po::supported_scalar_type<po::default_numeric_type>);

  static_assert(po::supported_scalar_type<po::scalar_field<double>::type>);
  static_assert(po::supported_scalar_type<po::scalar_field<float>::type>);

  static_assert(po::supported_scalar_type<int>);
  static_assert(po::supported_scalar_type<long>);
  static_assert(po::supported_scalar_type<long long>);
  static_assert(po::supported_scalar_type<double>);
  static_assert(po::supported_scalar_type<float>);

}

