#include "../../../polynomial.h"

#include <concepts>
#include <type_traits>

#include "expr_static_assert_test_symbols.h"

// N.B. Symbols `p`, `c`, `s`, `cp`, `cc`, `cs`, `P`, `C`, `S`, `CP`, `CC`, `CS`, are defined
// in expr_static_assert_test_symbols.h
void test_expr_unary_integral_subexpressions()
{
  using namespace static_asserts;

  // lvalue polynomial, compound v. variadic
  {
    using po::place;

    auto x = integral(integral(p, place{2, {-1, 1}}), place{1, {-1, 1}});
    auto y = integral(p, place{2, {-1, 1}}, place{1, {-1, 1}});

    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1 == &p);
    assert(&y.expr1.expr1 == &p);

    PO_LINE;
  }

  // rvalue polynomial, compound v. variadic
  {
    using po::place;

    auto x = integral(integral(P{}, place{2, {-1, 1}}), place{1, {-1, 1}});
    auto y = integral(P{}, place{2, {-1, 1}}, place{1, {-1, 1}});

    static_assert(std::same_as<decltype(x.expr1.expr1), CP>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1 != &y.expr1.expr1);

    PO_LINE;
  }

  // lvalue scalar_type, compound v. variadic
  {
    using po::place;

    auto x = integral(integral(s, place{2, {-1, 1}}), place{1, {-1, 1}});
    auto y = integral(s, place{2, {-1, 1}}, place{1, {-1, 1}});

    static_assert(std::same_as<decltype(x.expr1.expr1), const po::scalar_type&>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1 == &s);
    assert(&y.expr1.expr1 == &s);

    PO_LINE;
  }

  // lvalue const scalar_type, compound v. variadic
  {
    using po::place;

    auto x = integral(integral(cs, place{2, {-1, 1}}), place{1, {-1, 1}});
    auto y = integral(cs, place{2, {-1, 1}}, place{1, {-1, 1}});

    static_assert(std::same_as<decltype(x.expr1.expr1), const po::scalar_type&>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1 == &cs);
    assert(&y.expr1.expr1 == &cs);

    PO_LINE;
  }

  // lvalue constant, compound v. variadic
  {
    using po::place;

    auto x = integral(integral(c, place{2, {-1, 1}}), place{1, {-1, 1}});
    auto y = integral(c, place{2, {-1, 1}}, place{1, {-1, 1}});

    static_assert(std::same_as<decltype(x.expr1.expr1), CC&>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1 == &c);
    assert(&y.expr1.expr1 == &c);

    PO_LINE;
  }

  // rvalue constant, compound v. variadic
  {
    using po::place;

    auto x = integral(integral(C{}, place{2, {-1, 1}}), place{1, {-1, 1}});
    auto y = integral(C{}, place{2, {-1, 1}}, place{1, {-1, 1}});

    static_assert(std::same_as<decltype(x.expr1.expr1), CC>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1 != &y.expr1.expr1);

    PO_LINE;
  }

  // lvalue op lvalue, compound v. variadic
  {
    using po::place;

    auto x = integral(integral(p * p, place{2, {-1, 1}}), place{1, {-1, 1}});
    auto y = integral(p * p, place{2, {-1, 1}}, place{1, {-1, 1}});

    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1.expr1 == &p);
    assert(&x.expr1.expr1.expr2 == &p);
    assert(&y.expr1.expr1.expr1 == &p);
    assert(&y.expr1.expr1.expr2 == &p);

    PO_LINE;
  }

  // lvalue op lvalue (constexprs), compound v. variadic
  {
    using po::place;

    constexpr auto x = integral(integral(p * p, place{2, {-1, 1}}), place{1, {-1, 1}});
    constexpr auto y = integral(p * p, place{2, {-1, 1}}, place{1, {-1, 1}});

    static_assert(&x.expr1.expr1.expr1 == &p);
    static_assert(&x.expr1.expr1.expr2 == &p);
    static_assert(&y.expr1.expr1.expr1 == &p);
    static_assert(&y.expr1.expr1.expr2 == &p);

    static_assert(std::same_as<decltype(x), decltype(y)>);
  }

  // lvalue op (expr rvalue), compound v. variadic
  {
    using po::place;

    auto x = integral(integral(p * p - s, place{2, {-1, 1}}), place{1, {-1, 1}});
    auto y = integral(p * p - s, place{2, {-1, 1}}, place{1, {-1, 1}});

    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1.expr1.expr1 == &p);
    assert(&x.expr1.expr1.expr1.expr2 == &p);
    assert(&y.expr1.expr1.expr2.expr1 != &s);
    assert( y.expr1.expr1.expr2.expr1 ==  s);

    PO_LINE;
  }

}

namespace static_asserts
{
  template<typename E1>
  using I = po::expr_integral<E1>;
  using S = po::scalar_type;
  struct stala : po::parametric_interval
  {
    stala(): po::parametric_interval{{}, {{}, {}}} {}
  };

  static_assert(std::same_as<decltype( integral( P{}, stala{} ).expr1 ), const P>);
  static_assert(std::same_as<decltype( integral(CP{}, stala{} ).expr1 ), const P>);
  static_assert(std::same_as<decltype( integral( p  , stala{} ).expr1 ), const P&>);
  static_assert(std::same_as<decltype( integral(cp  , stala{} ).expr1 ), const P&>);

  static_assert(!std::is_reference_v<decltype(integral( P{}, stala{}).expr1)>);
  static_assert(!std::is_reference_v<decltype(integral(CP{}, stala{}).expr1)>);
  static_assert( std::is_reference_v<decltype(integral( p  , stala{}).expr1)>);
  static_assert( std::is_reference_v<decltype(integral(cp  , stala{}).expr1)>);

  static_assert(std::same_as<decltype( integral( P{}, stala{}) ), I< P >>);
  static_assert(std::same_as<decltype( integral(CP{}, stala{}) ), I<CP >>);
  static_assert(std::same_as<decltype( integral( p  , stala{}) ), I< P&>>);
  static_assert(std::same_as<decltype( integral(cp  , stala{}) ), I<CP&>>);

  static_assert(std::same_as<decltype( integral(integral( P{}, stala{}), stala{}) ), I<I< P >>>);
  static_assert(std::same_as<decltype( integral(integral(CP{}, stala{}), stala{}) ), I<I<CP >>>);
  static_assert(std::same_as<decltype( integral(integral( p  , stala{}), stala{}) ), I<I< P&>>>);
  static_assert(std::same_as<decltype( integral(integral(cp  , stala{}), stala{}) ), I<I<CP&>>>);

  static_assert(std::same_as<decltype( integral( P{}, stala{}, stala{}) ), I<I< P >>>);
  static_assert(std::same_as<decltype( integral(CP{}, stala{}, stala{}) ), I<I<CP >>>);
  static_assert(std::same_as<decltype( integral( p  , stala{}, stala{}) ), I<I< P&>>>);
  static_assert(std::same_as<decltype( integral(cp  , stala{}, stala{}) ), I<I<CP&>>>);

  static_assert(std::same_as<decltype( integral(integral(integral( P{}, stala{}), stala{}), stala{}) ), I<I<I< P >>>>);
  static_assert(std::same_as<decltype( integral(integral(integral(CP{}, stala{}), stala{}), stala{}) ), I<I<I<CP >>>>);
  static_assert(std::same_as<decltype( integral(integral(integral( p  , stala{}), stala{}), stala{}) ), I<I<I< P&>>>>);
  static_assert(std::same_as<decltype( integral(integral(integral(cp  , stala{}), stala{}), stala{}) ), I<I<I<CP&>>>>);

  static_assert(std::same_as<decltype( integral( P{}, stala{}, stala{}, stala{}) ), I<I<I< P >>>>);
  static_assert(std::same_as<decltype( integral(CP{}, stala{}, stala{}, stala{}) ), I<I<I<CP >>>>);
  static_assert(std::same_as<decltype( integral( p  , stala{}, stala{}, stala{}) ), I<I<I< P&>>>>);
  static_assert(std::same_as<decltype( integral(cp  , stala{}, stala{}, stala{}) ), I<I<I<CP&>>>>);

}

