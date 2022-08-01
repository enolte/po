#include "../../ops/expr_field_type.h"
#include "../../ops/is_expr_field_type.h"

#include "../../polynomial.h"

void test_expr_field_type()
{
  PO_LINE;
}

static_assert(std::same_as<const int, po::expr_field_type<int>>);
static_assert(std::same_as<const int&,po::expr_field_type<int&>>);
static_assert(std::same_as<const int, po::expr_field_type<int&&>>);
static_assert(std::same_as<const int, po::expr_field_type<const int>>);
static_assert(std::same_as<const int&,po::expr_field_type<const int&>>);
static_assert(std::same_as<const int, po::expr_field_type<const int&&>>);

static_assert(po::is_expr_field_type<po::expr_field_type<int>>);
static_assert(po::is_expr_field_type<po::expr_field_type<int&>>);
static_assert(po::is_expr_field_type<po::expr_field_type<int&&>>);
static_assert(po::is_expr_field_type<po::expr_field_type<const int>>);
static_assert(po::is_expr_field_type<po::expr_field_type<const int&>>);
static_assert(po::is_expr_field_type<po::expr_field_type<const int&&>>);


namespace po
{
  // The effect of po::expr_field_type<E>, C++11.
  template<typename E>
  using effect_of_expr_field_type =
    typename std::conditional<
      std::is_lvalue_reference_v<E>,
        const std::remove_reference_t<E>&,
      const std::remove_reference_t<E>
    >::type;

  static_assert(std::same_as<effect_of_expr_field_type<      int  >,  const int >);
  static_assert(std::same_as<effect_of_expr_field_type<      int& >,  const int&>);
  static_assert(std::same_as<effect_of_expr_field_type<      int&&>,  const int >);

  static_assert(std::same_as<effect_of_expr_field_type<const int  >,  const int >);
  static_assert(std::same_as<effect_of_expr_field_type<const int& >,  const int&>);
  static_assert(std::same_as<effect_of_expr_field_type<const int&&>,  const int >);

  static_assert(std::same_as<expr_field_type<      int  >,            const int >);
  static_assert(std::same_as<expr_field_type<      int& >,            const int&>);
  static_assert(std::same_as<expr_field_type<      int&&>,            const int >);

  static_assert(std::same_as<expr_field_type<const int  >,            const int >);
  static_assert(std::same_as<expr_field_type<const int& >,            const int&>);
  static_assert(std::same_as<expr_field_type<const int&&>,            const int >);

  // binary expression prototype
  template<typename E1, typename E2>
  struct X
  {
    using _E1 = E1;
    using _E2 = E2;

    using F1 = expr_field_type<_E1>;
    using F2 = expr_field_type<_E2>;

    F1 expr1;
    F2 expr2;
  };

  static_assert(std::is_const_v<X<polynomial, polynomial>::F1>);
  static_assert(std::is_const_v<X<polynomial, polynomial&>::F1>);

  static_assert(!po::is_expr_field_type<X<int        , int>::_E1>);
  static_assert(!po::is_expr_field_type<X<int&       , int>::_E1>);
  static_assert(!po::is_expr_field_type<X<int&&      , int>::_E1>);

  static_assert( po::is_expr_field_type<X<int        , int>::F1>);
  static_assert( po::is_expr_field_type<X<int&       , int>::F1>);
  static_assert( po::is_expr_field_type<X<int&&      , int>::F1>);

  static_assert(std::same_as<X<      int&&, int&>::_E1,                 int&&>);
  static_assert(std::same_as<X<      int& , int&>::_E1,                 int&>);
  static_assert(std::same_as<X<      int  , int&>::_E1,                 int>);

  static_assert(std::same_as<X<      int&&, int&>::F1,                  const int>);
  static_assert(std::same_as<X<      int& , int&>::F1,                  const int&>);
  static_assert(std::same_as<X<      int  , int&>::F1,                  const int>);

  static_assert(std::same_as<X<const int&&, int&>::_E1,                 const int&&>);
  static_assert(std::same_as<X<const int& , int&>::_E1,                 const int&>);
  static_assert(std::same_as<X<const int  , int&>::_E1,                 const int>);

  static_assert(std::same_as<X<const int&&, int&>::F1 ,                 const int>);
  static_assert(std::same_as<X<const int& , int&>::F1 ,                 const int&>);
  static_assert(std::same_as<X<const int  , int&>::F1 ,                 const int>);
}



