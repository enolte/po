#include "../../../polynomial.h"

#include <concepts>
#include <type_traits>

#include "expr_static_assert_test_symbols.h"

// N.B. Symbols `p`, `c`, `s`, `cp`, `cc`, `cs`, `P`, `C`, `S`, `CP`, `CC`, `CS`, are defined
// in expr_static_assert_test_symbols.h
void test_expr_unary_partial_derivative_subexpressions()
{
  using namespace static_asserts;
  using po::D;

  // lvalue polynomial
  {
    auto x = D(D(p, 2), 1);
    auto y = D(p, 2, 1);

    assert(&x.expr1.expr1 == &p);
    assert(&y.expr1.expr1 == &p);

    static_assert(std::same_as<decltype(x.expr1.expr1), CP&>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // rvalue polynomial
  {
    auto x = D(D(P{}, 2), 1);
    auto y = D(P{}, 2, 1);

    assert(&x.expr1.expr1 != &y.expr1.expr1);

    static_assert(std::same_as<decltype(x.expr1.expr1), CP>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // lvalue scalar_type
  {
    auto x = D(D(s, 2), 1);
    auto y = D(s, 2, 1);

    assert(&x.expr1.expr1 == &s);
    assert(&y.expr1.expr1 == &s);

    static_assert(std::same_as<decltype(x.expr1.expr1), CS&>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // rvalue scalar_type
  {
    auto x = D(D(S{}, 2), 1);
    auto y = D(S{}, 2, 1);

    assert(&x.expr1.expr1 != &y.expr1.expr1);

    static_assert(std::same_as<decltype(x.expr1.expr1), CS>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // lvalue const scalar_type
  {
    auto x = D(D(cs, 2), 1);
    auto y = D(cs, 2, 1);

    assert(&x.expr1.expr1 == &cs);
    assert(&y.expr1.expr1 == &cs);

    static_assert(std::same_as<decltype(x.expr1.expr1), CS&>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // rvalue const scalar_type
  {
    auto x = D(D(CS{}, 2), 1);
    auto y = D(CS{}, 2, 1);

    assert(&x.expr1.expr1 != &y.expr1.expr1);

    static_assert(std::same_as<decltype(x.expr1.expr1), CS>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // lvalue constant
  {
    auto x = D(D(c, 2), 1);
    auto y = D(c, 2, 1);

    assert(&x.expr1.expr1 == &c);
    assert(&y.expr1.expr1 == &c);

    static_assert(std::same_as<decltype(x.expr1.expr1), CC&>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // rvalue constant
  {
    auto x = D(D(C{}, 2), 1);
    auto y = D(C{}, 2, 1);

    assert(&x.expr1.expr1 != &y.expr1.expr1);

    static_assert(std::same_as<decltype(x.expr1.expr1), CC>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // lvalue op lvalue
  {
    auto x = D(D(p*p - s, 2), 1);
    auto y = D(p*p - s, 2, 1);

    assert(&x.expr1.expr1.expr1.expr1 == &p);
    assert(&x.expr1.expr1.expr1.expr2 == &p);
    assert(&x.expr1.expr1.expr2.expr1 != &s);
    assert( x.expr1.expr1.expr2.expr1 ==  s);

    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // lvalue op lvalue (constexprs)
  {
    // constexpr auto cs = s;

    constexpr auto x = D(D(p*p, 2), 1);
    constexpr auto y = D(p*p, 2, 1);

    static_assert(&x.expr1.expr1.expr1 == &p);
    static_assert(&y.expr1.expr1.expr1 == &p);

    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // constexpr with lvalue
  {
    constexpr auto x = D(D(p, 2), 1);
    constexpr auto y = D(p, 2, 1);

    static_assert(&x.expr1.expr1 == &p);
    static_assert(&y.expr1.expr1 == &p);

    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // lvalue op rvalue (constexpr)
  {
    constexpr auto x = D(D(p*S{}, 2), 1);
    constexpr auto y = D(p*S{}, 2, 1);

    static_assert(&x.expr1.expr1.expr1 == &p);
    static_assert(&y.expr1.expr1.expr1 == &p);

    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // lvalue op lvalue (constexpr)
  {
    constexpr double s = 3.7;
    constexpr auto x = D(D(p*s, 2), 1);
    constexpr auto y = D(p*s, 2, 1);

    static_assert(std::same_as<decltype(x.expr1.expr1.expr2), CC>);

    static_assert(&x.expr1.expr1.expr1 == &p);
    static_assert(&y.expr1.expr1.expr1 == &p);
    static_assert(&x.expr1.expr1.expr2.expr1 != &s);
    static_assert( x.expr1.expr1.expr2.expr1 ==  s);

    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // lvalue op {expr rvalue} (constexpr)
  {
    constexpr double s = 3.7;
    constexpr auto x = D(D(p*p - s, 2), 1);
    constexpr auto y = D(p*p - s, 2, 1);

    static_assert(std::same_as<decltype(x.expr1.expr1.expr2), CC>);

    static_assert(&x.expr1.expr1.expr1.expr1 == &p);
    static_assert(&y.expr1.expr1.expr1.expr1 == &p);
    static_assert(&x.expr1.expr1.expr1.expr2 == &p);
    static_assert(&y.expr1.expr1.expr1.expr2 == &p);

    static_assert(&x.expr1.expr1.expr2.expr1 != &s);
    static_assert( x.expr1.expr1.expr2.expr1 ==  s);

    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }
}

namespace static_asserts
{
  template<typename E1>
  using PD = po::expr_partial_derivative<E1>;

  using po::D;
  using R = po::rank_type;

  // N.B. Symbols `p` and `cp` are defined in expr_static_assert_test_symbols.h
  static_assert(std::same_as<decltype( D( P{}, R{}).expr1 ), const P>);
  static_assert(std::same_as<decltype( D(CP{}, R{}).expr1 ), const P>);
  static_assert(std::same_as<decltype( D( p  , R{}).expr1 ), const P&>);
  static_assert(std::same_as<decltype( D(cp  , R{}).expr1 ), const P&>);

  static_assert(po::is_polynomial<decltype(D( P{}, R{}).expr1)>);
  static_assert(po::is_polynomial<decltype(D(CP{}, R{}).expr1)>);
  static_assert(po::is_polynomial<decltype(D( p  , R{}).expr1)>);
  static_assert(po::is_polynomial<decltype(D(cp  , R{}).expr1)>);

  static_assert(!std::is_reference_v<decltype(D( P{}, R{}).expr1)>);
  static_assert(!std::is_reference_v<decltype(D(CP{}, R{}).expr1)>);
  static_assert( std::is_reference_v<decltype(D( p  , R{}).expr1)>);
  static_assert( std::is_reference_v<decltype(D(cp  , R{}).expr1)>);

  static_assert(std::same_as<decltype( D( P{}, R{}) ), PD< P >>);
  static_assert(std::same_as<decltype( D(CP{}, R{}) ), PD<CP >>);
  static_assert(std::same_as<decltype( D( p  , R{}) ), PD< P&>>);
  static_assert(std::same_as<decltype( D(cp  , R{}) ), PD<CP&>>);

  static_assert(std::same_as<decltype( D(D( P{}, R{}), R{}) ), PD<PD< P >>>);
  static_assert(std::same_as<decltype( D(D(CP{}, R{}), R{}) ), PD<PD<CP >>>);
  static_assert(std::same_as<decltype( D(D( p  , R{}), R{}) ), PD<PD< P&>>>);
  static_assert(std::same_as<decltype( D(D(cp  , R{}), R{}) ), PD<PD<CP&>>>);

  static_assert(std::same_as<decltype( D(D(D( P{}, R{}), R{}), R{}) ), PD<PD<PD< P >>>>);
  static_assert(std::same_as<decltype( D(D(D(CP{}, R{}), R{}), R{}) ), PD<PD<PD<CP >>>>);
  static_assert(std::same_as<decltype( D(D(D( p  , R{}), R{}), R{}) ), PD<PD<PD< P&>>>>);
  static_assert(std::same_as<decltype( D(D(D(cp  , R{}), R{}), R{}) ), PD<PD<PD<CP&>>>>);

  static_assert(std::same_as<decltype( D( P{}, R{}, R{}, R{}) ), PD<PD<PD< P >>>>);
  static_assert(std::same_as<decltype( D(CP{}, R{}, R{}, R{}) ), PD<PD<PD<CP >>>>);
  static_assert(std::same_as<decltype( D( p  , R{}, R{}, R{}) ), PD<PD<PD< P&>>>>);
  static_assert(std::same_as<decltype( D(cp  , R{}, R{}, R{}) ), PD<PD<PD<CP&>>>>);

}

