#include "../../../ops/subexpr_type.h"
#include "../../../ops/is_subexpr_type.h"

#include "../../../polynomial.h"

void test_is_subexpr_type()
{
  PO_LINE;
}

namespace po
{
  // std::is_const implements these facts:
  static_assert( std::is_const_v<const int>);
  static_assert(!std::is_const_v<const int&>);
  static_assert(!std::is_const_v<const int&&>);

  static_assert(!std::is_const_v<int>);
  static_assert(!std::is_const_v<int&>);
  static_assert(!std::is_const_v<int&&>);

  // is_subexpr_type implements these:
  static_assert(is_subexpr_type<const int>);
  static_assert(is_subexpr_type<const int&>);
  static_assert(is_subexpr_type<const int&&>);

  static_assert(!is_subexpr_type<int>);
  static_assert(!is_subexpr_type<int&>);
  static_assert(!is_subexpr_type<int&&>);
}

static_assert(std::same_as<const int, po::subexpr_type<int>>);
static_assert(std::same_as<const int&,po::subexpr_type<int&>>);
static_assert(std::same_as<const int, po::subexpr_type<int&&>>);
static_assert(std::same_as<const int, po::subexpr_type<const int>>);
static_assert(std::same_as<const int&,po::subexpr_type<const int&>>);
static_assert(std::same_as<const int, po::subexpr_type<const int&&>>);

static_assert(po::is_subexpr_type<po::subexpr_type<int>>);
static_assert(po::is_subexpr_type<po::subexpr_type<int&>>);
static_assert(po::is_subexpr_type<po::subexpr_type<int&&>>);
static_assert(po::is_subexpr_type<po::subexpr_type<const int>>);
static_assert(po::is_subexpr_type<po::subexpr_type<const int&>>);
static_assert(po::is_subexpr_type<po::subexpr_type<const int&&>>);


// The effect of po::subexpr_type<E>, C++11.
template<typename E>
using effect_of_subexpr_type =
  typename std::conditional<
    std::is_lvalue_reference_v<E>,
      const std::remove_reference_t<E>&,
    const std::remove_reference_t<E>
  >::type;

static_assert(std::same_as<effect_of_subexpr_type<      int  >,  const int >);
static_assert(std::same_as<effect_of_subexpr_type<      int& >,  const int&>);
static_assert(std::same_as<effect_of_subexpr_type<      int&&>,  const int >);

static_assert(std::same_as<effect_of_subexpr_type<const int  >,  const int >);
static_assert(std::same_as<effect_of_subexpr_type<const int& >,  const int&>);
static_assert(std::same_as<effect_of_subexpr_type<const int&&>,  const int >);

static_assert(std::same_as<po::subexpr_type<      int  >,            const int >);
static_assert(std::same_as<po::subexpr_type<      int& >,            const int&>);
static_assert(std::same_as<po::subexpr_type<      int&&>,            const int >);

static_assert(std::same_as<po::subexpr_type<const int  >,            const int >);
static_assert(std::same_as<po::subexpr_type<const int& >,            const int&>);
static_assert(std::same_as<po::subexpr_type<const int&&>,            const int >);

// binary expression prototype
template<typename E1, typename E2>
struct X
{
  using _E1 = E1;
  using _E2 = E2;

  using F1 = po::subexpr_type<_E1>;
  using F2 = po::subexpr_type<_E2>;

  F1 expr1;
  F2 expr2;
};

static_assert(std::is_const_v<X<po::polynomial, po::polynomial>::F1>);
static_assert(std::is_const_v<X<po::polynomial, po::polynomial&>::F1>);

static_assert(!po::is_subexpr_type<X<int        , int>::_E1>);
static_assert(!po::is_subexpr_type<X<int&       , int>::_E1>);
static_assert(!po::is_subexpr_type<X<int&&      , int>::_E1>);

static_assert( po::is_subexpr_type<X<int        , int>::F1>);
static_assert( po::is_subexpr_type<X<int&       , int>::F1>);
static_assert( po::is_subexpr_type<X<int&&      , int>::F1>);

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



