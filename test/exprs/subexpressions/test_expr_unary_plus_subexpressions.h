#include "../../../polynomial.h"
#include "expr_static_assert_test_symbols.h"

#include <concepts>

void test_expr_unary_plus_subexpressions()
{
   PO_LINE;
}

namespace static_asserts
{
  template<typename E1>
  using uplus = po::expr_unary_plus<E1>;

  static_assert(!std::is_reference_v<decltype( (+(P{})).expr1 )>);

  static_assert(std::same_as<decltype( +(P{}))       , uplus<P>>);
  static_assert(std::same_as<decltype((+(P{})).expr1), const P>);

  static_assert(std::is_reference_v<decltype( (+p).expr1 )>);
  static_assert(std::same_as<decltype( +p)       , uplus<P&>>);
  static_assert(std::same_as<decltype((+p).expr1), const P&>);

  static_assert(std::is_reference_v<decltype( (+cp).expr1 )>);
  static_assert(std::same_as<decltype( +cp)       , uplus<const P&>>);
  static_assert(std::same_as<decltype((+cp).expr1), const P&>);

  static_assert(std::is_const_v<std::remove_reference_t<decltype((+cp).expr1)>>);

}
