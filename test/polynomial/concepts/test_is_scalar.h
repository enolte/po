#include "../../../ops/is_scalar.h"
#include "../../../types/scalar.h"

void test_is_scalar()
{
  PO_LINE;
}

namespace static_asserts
{
  static_assert(po::is_scalar<po::scalar_type>);

  static_assert(po::is_scalar<int>);
  static_assert(po::is_scalar<long>);
  static_assert(po::is_scalar<long long>);
  static_assert(po::is_scalar<double>);
  static_assert(po::is_scalar<float>);

}

