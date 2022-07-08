#include "../../ops/expr.h"

#include <cassert>

namespace po_test
{
  static bool called_Y  = false;
  static bool called_Y2 = false;
  static bool called_Z  = false;

  void reset()
  {
    called_Y = called_Y2 = called_Z = false;
  }

  // A type without an expr base type
  struct Y
  {
    template<typename ...X>
    constexpr int operator()(X... x) const
    {
      called_Y = true;
      return 1;
    }
  };

  // A type with the wrong expr base type (miswired)
  struct Y2 : po::expr<Y>
  {
    using base_type = po::expr<Y>;

    // Verify wrong expr type accessed through the base type
    static_assert(std::same_as<base_type::expr_type, Y>);

    template<typename ...X>
    constexpr int operator()(X... x) const
    {
      called_Y2 = true;
      return 2;
    }
  };

  // A type with a correct expr base type
  struct Z : po::expr<Z>
  {
    using base_type = po::expr<Z>;
    template<typename ...X>
    constexpr int operator()(X... x) const
    {
      called_Z = true;
      return 3;
    }

  };
}

void test_expr()
{
  using namespace po_test;
  using namespace po;

  // Y: No expr base type: expr call
  {
    constexpr po::expr<Y> expr{};
    const auto v = expr(0, 1, 2);

    assert(called_Y && !called_Y2);
    assert(v == 1);
    reset();
  }

  // Y2: Wrong expr base type: direct call
  {
    constexpr Y2 y2{};
    const auto v = y2(0, 1, 2);

    PO_ASSERT(!called_Y && called_Y2, called_Y2);
    assert(v == 2);
    reset();
  }

  // Y2: Wrong expr base type: expr-cast call
  {
    constexpr Y2 y2{};
    const auto v = ((const Y2::base_type&)(y2))(0, 1, 2);

    // >>> Wrong impl called! Called Y::op(....), not Y2::op(....)
    assert(called_Y && !called_Y2);
    assert(v == 1);
    reset();
  }

  // Y2: Wrong expr base type: expr call from correct base type even though Y2 is miswired
  {
    constexpr po::expr<Y2> expr{};

    const auto v = expr(0, 1, 2);

    PO_ASSERT(!called_Y && called_Y2, called_Y << ", " << called_Y2);
    assert(v == 2);
    reset();
  }

  // Z: Correct expr base type, direct call
  {
    constexpr Z z{};
    PO_LINE; const auto v = z(0, 1, 2);

    assert(called_Z);
    assert(v == 3);
    reset();
  }

  // Z: Correct expr base type, expr-cast call
  {
    constexpr Z z{};
    PO_LINE; const auto v = ((const Z::base_type)(z))(0, 1, 2);

    assert(called_Z);
    assert(v == 3);
    reset();
  }

  PO_LINE;
}

namespace static_asserts
{
  using po::expr;
  using namespace po_test;

  // Y: Verify expr<>::expr_type is the correct type
  static_assert(std::same_as<expr<Y>::expr_type, Y>);

  // Y2: Verify miswired
  static_assert(std::same_as<Y2::base_type, expr<Y>>);
  static_assert(std::same_as<Y2::base_type::expr_type, Y>);

  // Y2: Even for a miswired type T, expr<T> identifies the correct type T.
  static_assert(std::same_as<expr<Y2>::expr_type, Y2>);

  // Z: Verify correctly wired
  static_assert(std::same_as<Z::base_type, expr<Z>>);
  static_assert(std::same_as<Z::base_type::expr_type, Z>);
  static_assert(std::same_as<po::expr<Z>::expr_type, Z>);
}

