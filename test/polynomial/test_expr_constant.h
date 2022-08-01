#include "../../ops/expr_constant.h"

#include "../errors.h"

#include <concepts>
#include <cassert>

void test_expr_constant()
{
  {
    po::expr_constant c{4.2};
    assert(c() == 4.2);
    assert(c(7.2) == 4.2);
    assert(c(-1, 3, 4, 5.47) == 4.2);
  }

  {
    po::expr_constant c{4.2f};
    assert(po_test::near_rel(c(), 4.2, 0x1p-23));
    assert(po_test::near_rel(c(7.2), 4.2, 0x1p-23));
    assert(po_test::near_rel(c(-1, 3, 4, 5.47), 4.2, 0x1p-23));
  }

  {
    po::expr_constant c{13};
    assert(c() == 13);
    assert(c(7.2) == 13);
    assert(c(-1, 3, 4, 5.47) == 13);
  }

  {
    po::expr_constant c{(short)13};
    assert(c() == 13);
    assert(c(7.2) == 13);
    assert(c(-1, 3, 4, 5.47) == 13);
  }
}

namespace static_asserts
{
  static_assert(po::is_constant<po::scalar_type>);
  static_assert(po::is_constant<po::expr_constant>);
  static_assert(po::is_unary_expression<po::expr_constant>);

  static_assert(std::same_as<decltype(po::expr_constant{{}}()), po::scalar_type>);
  static_assert(std::same_as<decltype(po::expr_constant{{}}.expr1), const po::scalar_type>);
}

