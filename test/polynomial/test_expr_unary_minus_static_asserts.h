#include "../../polynomial.h"

#include <concepts>

namespace static_asserts
{
  using P = po::polynomial;

  template<typename E1>
  using uminus = po::expr_unary_minus<E1>;

  // rvalues
  static_assert(!std::is_reference_v<decltype( (-(P{})).expr1 )>);

  static_assert(std::same_as<decltype( -(P{}))       , uminus<P>>);
  static_assert(std::same_as<decltype((-(P{})).expr1), const P>);

  // lvalues
  namespace static_asserts_unary_minus
  {
    P p{};

    static_assert(!std::is_reference_v<decltype( (-p).expr1 )>);
    static_assert(std::same_as<decltype( -p)       , uminus<P>>);
    static_assert(std::same_as<decltype((-p).expr1), const P>);

    const P cp{};
    static_assert(!std::is_reference_v<decltype( (-cp).expr1 )>);
    static_assert(std::same_as<decltype( -cp)       , uminus<P>>);
    static_assert(std::same_as<decltype((-cp).expr1), const P>);

    static_assert(std::is_const_v<decltype((-cp).expr1)>);
  }

}
