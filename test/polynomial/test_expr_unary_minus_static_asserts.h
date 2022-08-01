#include "../../polynomial.h"
#include "expr_static_assert_test_symbols.h"

#include <concepts>

namespace static_asserts
{
  template<typename E1>
  using uminus = po::expr_unary_minus<E1>;

  static_assert(!std::is_reference_v<decltype( (-(P{})).expr1 )>);

  static_assert(std::same_as<decltype( -(P{}))       , uminus<P>>);
  static_assert(std::same_as<decltype((-(P{})).expr1), const P>);

  static_assert(std::is_reference_v<decltype( (-p).expr1 )>);
  static_assert(std::same_as<decltype( -p)       , uminus<P&>>);
  static_assert(std::same_as<decltype((-p).expr1), const P&>);

  static_assert(std::is_reference_v<decltype( (-cp).expr1 )>);
  static_assert(std::same_as<decltype( -cp)       , uminus<const P&>>);
  static_assert(std::same_as<decltype((-cp).expr1), const P&>);

  static_assert(std::is_const_v<std::remove_reference_t<decltype((-cp).expr1)>>);

}
