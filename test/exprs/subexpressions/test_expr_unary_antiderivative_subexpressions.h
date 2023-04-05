#include "../../../polynomial.h"

#include <concepts>
#include <type_traits>

#include "expr_static_assert_test_symbols.h"

// N.B. Symbols `p`, `c`, `s`, `cp`, `cc`, `cs`, `P`, `C`, `S`, `CP`, `CC`, `CS`, are defined
// in expr_static_assert_test_symbols.h
void test_expr_unary_antiderivative_subexpressions()
{
  using namespace static_asserts;

  // lvalue scalar_type
  {
    auto x = po::antiderivative(s, 2);

    assert(&x.expr1.expr1 != &s);

    PO_LINE;
  }

  // rvalue scalar_type
  {
    auto x = po::antiderivative(std::move(s), 2);

    assert(&x.expr1.expr1 != &s);

    PO_LINE;
  }

  // lvalue constant
  {
    auto x = po::antiderivative(c, 2);

    assert(&x.expr1 != &c);
    assert(x.expr1.expr1 == c.expr1);

    PO_LINE;
  }

  // rvalue constant
  {
    auto x = po::antiderivative(std::move(c), 2);

    assert(&x.expr1 != &c);
    assert(x.expr1.expr1 == c.expr1);

    PO_LINE;
  }

  // lvalue polynomial
  {
    auto x = po::antiderivative(p, 2);

    assert(&x.expr1 == &p);

    PO_LINE;
  }

  // rvalue polynomial
  {
    auto x = po::antiderivative(std::move(p), 2);

    assert(&x.expr1 != &p);

    PO_LINE;
  }

  // TODO
  // lvalue polynomial, compound
  {
    auto x = antiderivative(antiderivative(p, 2), 2);

    assert(&x.expr1.expr1 == &p);

    PO_LINE;
  }

  // rvalue polynomial, compound
  {
    auto x = antiderivative(antiderivative(std::move(p), 2), 2);

    assert(&x.expr1.expr1 != &p);

    PO_LINE;
  }

  // lvalue polynomial, compound v. variadic
  {
    auto x = antiderivative(antiderivative(p, 2), 1);
    auto y = antiderivative(p, 2, 1);

    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1 == &p);
    assert(&y.expr1.expr1 == &p);

    PO_LINE;
  }

  // rvalue polynomial, compound v. variadic
  {
    auto x = antiderivative(antiderivative(P{}, 2), 1);
    auto y = antiderivative(P{}, 2, 1);

    static_assert(std::same_as<decltype(x.expr1.expr1), CP>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1 != &y.expr1.expr1);

    PO_LINE;
  }

  // lvalue scalar_type, compound v. variadic
  {
    auto x = antiderivative(po::antiderivative(s, 2), 1);
    auto y = po::antiderivative(s, 2, 1);

    static_assert(std::same_as<decltype(x.expr1.expr1), const po::expr_constant>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1.expr1 != &s);
    assert(&y.expr1.expr1.expr1 != &s);

    PO_LINE;
  }

  // lvalue const scalar_type, compound v. variadic
  {
    auto x = antiderivative(po::antiderivative(cs, 2), 1);
    auto y = po::antiderivative(cs, 2, 1);

    static_assert(std::same_as<decltype(x.expr1.expr1), const po::expr_constant>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1.expr1 != &cs);
    assert(&y.expr1.expr1.expr1 != &cs);

    PO_LINE;
  }

  // lvalue constant, compound v. variadic
  {
    auto x = antiderivative(antiderivative(c, 2), 1);
    auto y = antiderivative(c, 2, 1);

    static_assert(std::same_as<decltype(x.expr1.expr1), const po::expr_constant>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1 != &c);
    assert(&y.expr1.expr1 != &c);

    PO_LINE;
  }

  // rvalue constant, compound v. variadic
  {
    auto x = antiderivative(antiderivative(C{}, 2), 1);
    auto y = antiderivative(C{}, 2, 1);

    static_assert(std::same_as<decltype(x.expr1.expr1), const po::expr_constant>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1 != &y.expr1.expr1);

    PO_LINE;
  }

  // lvalue op lvalue, compound v. variadic
  {
    auto x = antiderivative(antiderivative(p * p, 2), 1);
    auto y = antiderivative(p * p, 2, 1);

    static_assert(std::same_as<decltype(x.expr1.expr1.expr1), const po::polynomial&>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1.expr1 == &p);
    assert(&x.expr1.expr1.expr2 == &p);
    assert(&y.expr1.expr1.expr1 == &p);
    assert(&y.expr1.expr1.expr2 == &p);

    PO_LINE;
  }

  // lvalue op lvalue (constexprs), compound v. variadic
  {
    constexpr auto x = antiderivative(antiderivative(p * p, 2), 1);
    constexpr auto y = antiderivative(p * p, 2, 1);

    static_assert(&x.expr1.expr1.expr1 == &p);
    static_assert(&x.expr1.expr1.expr2 == &p);
    static_assert(&y.expr1.expr1.expr1 == &p);
    static_assert(&y.expr1.expr1.expr2 == &p);

    static_assert(std::same_as<decltype(x.expr1.expr1.expr1), const po::polynomial&>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    PO_LINE;
  }

  // lvalue op {expr rvalue}, compound v. variadic
  {
    auto x = antiderivative(antiderivative(p * p - s, 2), 1);
    auto y = antiderivative(p * p - s, 2, 1);

    static_assert(std::same_as<decltype(x.expr1.expr1.expr1.expr1), const po::polynomial&>);
    static_assert(std::same_as<decltype(x.expr1.expr1.expr1.expr2), const po::polynomial&>);
    static_assert(std::same_as<decltype(x.expr1.expr1.expr2), const po::expr_constant>);
    static_assert(std::same_as<decltype(x.expr1.expr1.expr2.expr1), const po::scalar_type>);
    static_assert(std::same_as<decltype(x), decltype(y)>);

    assert(&x.expr1.expr1.expr1.expr1 == &p);
    assert(&x.expr1.expr1.expr1.expr2 == &p);
    assert(&y.expr1.expr1.expr2.expr1 != &s);
    assert( y.expr1.expr1.expr2.expr1 ==  s);

    PO_LINE;
  }
}

#include "../expr_unary_antiderivative_evaluate/A.h"

namespace static_asserts
{
  static_assert(std::same_as<decltype(antiderivative(D(p, 0), 0))::F1::F1, const po::polynomial&>);
  static_assert(std::same_as<decltype(antiderivative(D(p, 0), 0))::F1, const po::expr_partial_derivative<po::polynomial&>>);
  static_assert(std::same_as<decltype(antiderivative(D(p, 0), 0)), po::expr_antiderivative<po::expr_partial_derivative<po::polynomial&>>>);

  template<po::expression E1>
  using expr_A = po::expr_antiderivative<E1>;

  static_assert(std::same_as<decltype( antiderivative( P{}, {} ).expr1 ), const P>);
  static_assert(std::same_as<decltype( antiderivative(CP{}, {} ).expr1 ), const P>);
  static_assert(std::same_as<decltype( antiderivative( p  , {} ).expr1 ), const P&>);
  static_assert(std::same_as<decltype( antiderivative(cp  , {} ).expr1 ), const P&>);

  static_assert(!std::is_reference_v<decltype(antiderivative( P{}, {}).expr1)>);
  static_assert(!std::is_reference_v<decltype(antiderivative(CP{}, {}).expr1)>);
  static_assert( std::is_reference_v<decltype(antiderivative( p  , {}).expr1)>);
  static_assert( std::is_reference_v<decltype(antiderivative(cp  , {}).expr1)>);

  static_assert(std::same_as<expr_A< P >, decltype( antiderivative( P{}, {}) )>);
  static_assert(std::same_as<expr_A<CP >, decltype( antiderivative(CP{}, {}) )>);
  static_assert(std::same_as<expr_A< P&>, decltype( antiderivative( p  , {}) )>);
  static_assert(std::same_as<expr_A<CP&>, decltype( antiderivative(cp  , {}) )>);

  static_assert(std::same_as<expr_A<expr_A< P >>, decltype( A(A( P{}, {}), {}) )>);
  static_assert(std::same_as<expr_A<expr_A<CP >>, decltype( A(A(CP{}, {}), {}) )>);
  static_assert(std::same_as<expr_A<expr_A< P&>>, decltype( A(A( p  , {}), {}) )>);
  static_assert(std::same_as<expr_A<expr_A<CP&>>, decltype( A(A(cp  , {}), {}) )>);

  static_assert(std::same_as<expr_A<expr_A< P >>, decltype( antiderivative( P{}, po::rank_type{}, po::rank_type{}) )>);
  static_assert(std::same_as<expr_A<expr_A<CP >>, decltype( antiderivative(CP{}, po::rank_type{}, po::rank_type{}) )>);
  static_assert(std::same_as<expr_A<expr_A< P&>>, decltype( antiderivative( p  , po::rank_type{}, po::rank_type{}) )>);
  static_assert(std::same_as<expr_A<expr_A<CP&>>, decltype( antiderivative(cp  , po::rank_type{}, po::rank_type{}) )>);

  static_assert(std::same_as<expr_A<expr_A<expr_A< P >>>, decltype( antiderivative(antiderivative(antiderivative( P{}, po::rank_type{}), po::rank_type{}), po::rank_type{}) )>);
  static_assert(std::same_as<expr_A<expr_A<expr_A<CP >>>, decltype( antiderivative(antiderivative(antiderivative(CP{}, po::rank_type{}), po::rank_type{}), po::rank_type{}) )>);
  static_assert(std::same_as<expr_A<expr_A<expr_A< P&>>>, decltype( antiderivative(antiderivative(antiderivative( p  , po::rank_type{}), po::rank_type{}), po::rank_type{}) )>);
  static_assert(std::same_as<expr_A<expr_A<expr_A<CP&>>>, decltype( antiderivative(antiderivative(antiderivative(cp  , po::rank_type{}), po::rank_type{}), po::rank_type{}) )>);

  static_assert(std::same_as<expr_A<expr_A<expr_A< P >>>, decltype( antiderivative( P{}, po::rank_type{}, po::rank_type{}, po::rank_type{}) )>);
  static_assert(std::same_as<expr_A<expr_A<expr_A<CP >>>, decltype( antiderivative(CP{}, po::rank_type{}, po::rank_type{}, po::rank_type{}) )>);
  static_assert(std::same_as<expr_A<expr_A<expr_A< P&>>>, decltype( antiderivative( p  , po::rank_type{}, po::rank_type{}, po::rank_type{}) )>);
  static_assert(std::same_as<expr_A<expr_A<expr_A<CP&>>>, decltype( antiderivative(cp  , po::rank_type{}, po::rank_type{}, po::rank_type{}) )>);
}
