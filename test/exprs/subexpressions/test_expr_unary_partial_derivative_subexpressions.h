#include "../../../polynomial.h"

#include <concepts>
#include <type_traits>

#include "expr_static_assert_test_symbols.h"

void test_expr_unary_partial_derivative_subexpressions()
{
   PO_LINE;
}

namespace static_asserts
{
  template<typename E1>
  using PD = po::expr_partial_derivative<E1>;

  using po::D;

  // N.B. Symbols `p` and `cp` are defined in expr_static_assert_test_symbols.h
  static_assert(std::same_as<decltype( D(CP{}, {}).expr1 ), const P>);
  static_assert(std::same_as<decltype( D(cp  , {}).expr1 ), const P&>);
  static_assert(std::same_as<decltype( D( P{}, {}).expr1 ), const P>);
  static_assert(std::same_as<decltype( D( p  , {}).expr1 ), const P&>);

  static_assert(po::is_polynomial<decltype(D(CP{}, {}).expr1)>);
  static_assert(po::is_polynomial<decltype(D( P{}, {}).expr1)>);
  static_assert(po::is_polynomial<decltype(D(cp  , {}).expr1)>);
  static_assert(po::is_polynomial<decltype(D( p  , {}).expr1)>);

  static_assert(!std::is_reference_v<decltype(D( P{}, {}).expr1)>);
  static_assert(!std::is_reference_v<decltype(D(CP{}, {}).expr1)>);
  static_assert( std::is_reference_v<decltype(D( p  , {}).expr1)>);
  static_assert( std::is_reference_v<decltype(D(cp  , {}).expr1)>);

  static_assert(std::same_as<decltype( D( P{}, {}) ), PD< P >>);
  static_assert(std::same_as<decltype( D( p  , {}) ), PD< P&>>);
  static_assert(std::same_as<decltype( D(CP{}, {}) ), PD<CP >>);
  static_assert(std::same_as<decltype( D(cp  , {}) ), PD<CP&>>);

  static_assert(std::same_as<decltype( D(D( P{}, {}), {}) ), PD<PD< P >>>);
  static_assert(std::same_as<decltype( D(D( p  , {}), {}) ), PD<PD< P&>>>);
  static_assert(std::same_as<decltype( D(D(CP{}, {}), {}) ), PD<PD<CP >>>);
  static_assert(std::same_as<decltype( D(D(cp  , {}), {}) ), PD<PD<CP&>>>);

  static_assert(std::same_as<decltype( D(D(D( P{}, {}), {}), {}) ), PD<PD<PD< P >>>>);
  static_assert(std::same_as<decltype( D(D(D( p  , {}), {}), {}) ), PD<PD<PD< P&>>>>);
  static_assert(std::same_as<decltype( D(D(D(CP{}, {}), {}), {}) ), PD<PD<PD<CP >>>>);
  static_assert(std::same_as<decltype( D(D(D(cp  , {}), {}), {}) ), PD<PD<PD<CP&>>>>);

}

