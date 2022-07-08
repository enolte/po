#include "../../polynomial.h"

#include <concepts>

namespace static_asserts
{
  using P = po::polynomial;
  using D = po::D;

  static_assert(po::is_unary_expression<po::D>);

  // D(P, place)
  static_assert(std::same_as<decltype( D(P{}, {}).expr1), const P&>);
}

