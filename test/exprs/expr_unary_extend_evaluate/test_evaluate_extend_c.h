#include "../../../ops/expr_extend.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_extend_c()
{
  // rank 0 --> rank 3, test 0
  {
    auto x = po::extend(6.5, 3, 1);

    assert(compare::equal(x.places, {1}));
    assert(x.rank == 3);

    assert(x(1,2,3) != x(1,2,3));

    PO_LINE;
  }

  // rank 0 --> rank 3, test 0.5
  {
    auto x = po::extend(6.5, 3);

    assert(compare::equal(x.places, {}));
    assert(x.rank == 3);

    assert(x(1,2,3) == 6.5);

    PO_LINE;
  }

  // rank 0 --> rank 3, test 1
  {
    auto x = po::extend(3.3, 3);

    assert(compare::equal(x.places, {}));
    assert(x.rank == 3);

    po::scalar_type y = x(0, 1, 2);
    PO_ASSERT(y == 3.3, y);

    PO_LINE;
  }

  // rank 0 --> rank 3, test 2
  {
    auto x = po::extend(po::expr_constant{3.3}, 3);

    assert(compare::equal(x.places, {}));
    assert(x.rank == 3);

    po::scalar_type y = x(0, 1, 2);
    PO_ASSERT(y == 3.3, y);

    PO_LINE;
  }

  // rank 0 --> rank 3, test 3, too many places
  {
    auto x = po::extend(po::expr_constant{3.3}, 3, 2);

    assert(compare::equal(x.places, {2}));
    assert(x.rank == 3);

    po::scalar_type y = x(0, 1, 2);
    PO_ASSERT(y != y, y);

    PO_LINE;
  }

  // rank 0 --> rank 3, test 4, too many places
  {
    const po::expr_constant c{3.3};
    auto x = po::extend(c, 3, 2);

    assert(compare::equal(x.places, {2}));
    assert(x.rank == 3);

    po::scalar_type y = x(0, 1, 2);
    PO_ASSERT(y != y, y);

    PO_LINE;
  }

  // rank 0 --> rank 3, test 5
  {
    const po::expr_constant c{3.3};
    auto x = po::extend(c, 3);

    assert(compare::equal(x.places, {}));
    assert(x.rank == 3);

    po::scalar_type y = x(0, 1, 2);
    PO_ASSERT(y == 3.3, y);

    PO_LINE;
  }

  // rank 0 --> rank 3, test 6
  {
    const po::scalar_type s{3.3};
    auto x = po::extend(s, 3);

    assert(compare::equal(x.places, {}));
    assert(x.rank == 3);

    po::scalar_type y = x(0, 1, 2);
    PO_ASSERT(y == 3.3, y);

    PO_LINE;
  }
}

