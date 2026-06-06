#include "../../../ops/expr_extend.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_expr_nullary_extend_c()
{
  {
    volatile int pos = 3;
    auto i = [&pos]{ return pos; };
    auto x = po::extend(6.5, i());
    assert(x.rank == 3);
    static_assert(std::same_as<decltype(x), po::expr_extend<double>>);
    assert(x(1,2,3) == 6.5);
    PO_LINE;
  }

  // rank 0 (double) --> rank 3, test 0
  {
    auto x = po::extend(6.5, 3);
    assert(x.rank == 3);
    static_assert(std::same_as<decltype(x), po::expr_extend<double>>);
    assert(x(1,2,3) == 6.5);
    PO_LINE;
  }

  // rank 0 (double) --> rank 3, test 1
  {
    const po::scalar_type s{3.3};
    auto x = po::extend(s, 3);
    assert(x.rank == 3);
    static_assert(std::same_as<decltype(x), po::expr_extend<double>>);
    po::scalar_type y = x(0, 1, 2);
    PO_ASSERT(y == 3.3, y);
    PO_LINE;
  }

  // rank 0 (expr_constant) --> rank 3, test 2
  {
    auto x = po::extend(po::expr_constant{3.3}, 3);
    assert(x.rank == 3);
    static_assert(std::same_as<decltype(x), po::expr_extend<double>>);
    po::scalar_type y = x(0, 1, 2);
    PO_ASSERT(y == 3.3, y);
    PO_LINE;
  }

  // rank 0 (expr_constant) --> rank 3, test 3, multiple places
  {
    auto x = po::extend(po::expr_constant{3.3}, 3, 2);
    assert(x.rank == 3);
    static_assert(std::same_as<decltype(x), po::expr_extend<double>>);
    po::scalar_type y = x(0, 1, 2);
    PO_ASSERT(y == 3.3, y);
    PO_LINE;
  }

  // rank 0 (const expr_constant) --> rank 3, test 4, multiple places
  {
    const po::expr_constant c{3.3};
    auto x = po::extend(c, 3, 2);
    assert(x.rank == 3);
    static_assert(std::same_as<decltype(x), po::expr_extend<double>>);
    po::scalar_type y = x(0, 1, 2);
    PO_ASSERT(y = 3.3, y);
    PO_LINE;
  }
}




