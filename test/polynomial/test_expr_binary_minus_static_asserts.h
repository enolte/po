#include "../../polynomial.h"

#include <concepts>

namespace static_asserts
{
  using P = po::polynomial;
  using C = po::expr_constant;

  template<typename E1, typename E2>
  using minus = po::expr_binary_minus<E1, E2>;

  // polynomial - scalar
  static_assert(std::same_as<decltype( P{} - C{}), minus<const P&, const C&>>);
  static_assert(std::same_as<decltype((P{} - C{}).expr2), const C&>);
  static_assert(std::same_as<decltype((P{} - C{}).expr1), const P&>);

  namespace static_asserts_p_minus_c
  {
    po::polynomial p{{0, {0}}};
    auto x = p - -4;
    static_assert(std::same_as<decltype(x), minus<const P&, const C>>);
  }

  namespace static_asserts_c_minus_p
  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    auto x = c - p;
    static_assert(std::same_as<decltype(x), minus<const C, const P&>>);
  }

  namespace static_asserts_p_minus_c_minus_c
  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    static_assert(std::same_as<
      decltype((p - p) - c),
      minus<const minus<const P&, const P&>&, const C>
    >);
  }


  // scalar - polynomial
  static_assert(std::same_as<decltype( C{} - P{}), minus<const C&, const P&>>);
  static_assert(std::same_as<decltype((C{} - P{}).expr2), const P&>);
  static_assert(std::same_as<decltype((C{} - P{}).expr1), const C&>);


  static_assert(std::same_as<decltype( C{} - (C{} -  P{})), minus<const C&, const minus<const C&, const P&>&>>);
  static_assert(std::same_as<decltype((C{} -  C{}) - P{} ), minus<const minus<const C&, const C&>&, const P&>>);

  // polynomial - polynomial
  static_assert(std::same_as<decltype(P{} - P{}), minus<const P&, const P&>>);
  static_assert(std::same_as<decltype((P{} - P{}).expr2), const P&>);
  static_assert(std::same_as<decltype((P{} - P{}).expr1), const P&>);


  // (polynomial - polynomial) - polynomial
  static_assert(std::same_as<decltype( ( P{} - P{}) - P{} ), minus<const minus<const P&, const P&>&, const P&>>);
  static_assert(std::same_as<decltype( ((P{} - P{}) - P{} ).expr2), const P&>);
  static_assert(std::same_as<decltype( ((P{} - P{}) - P{} ).expr1), const minus<const P&, const P&>&>);


  // polynomial - (polynomial - polynomial)
  static_assert(std::same_as<decltype(  P{} - (P{} - P{}) ), minus<const P&, const minus<const P&, const P&>&>>);
  static_assert(std::same_as<decltype( (P{} - (P{} - P{}) ).expr2), const minus<const P&, const P&>&>);
  static_assert(std::same_as<decltype( (P{} - (P{} - P{}) ).expr1), const P&>);


  // LR
  // constant - constant - polynomial
  static_assert(std::same_as<decltype( C{} -  C{}  - P{} ), decltype((C{} - C{}) - P{})>);

  // polynomial - polynomial - polynomial
  static_assert(std::same_as<decltype(P{} - P{} - P{}), decltype((P{} - P{}) - P{})>);

  // polynomial - polynomial - polynomial - polynomial
  static_assert(std::same_as<decltype(P{} - P{} - P{} - P{}), decltype(((P{} - P{}) - P{}) - P{})>);

}
