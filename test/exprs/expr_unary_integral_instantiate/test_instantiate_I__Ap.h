#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_I__Ap()
{
  {
    po::polynomial p           {{2  , {1, 1, 1, 1}}};

    const auto expr_a1p = antiderivative(p, 1);

    const po::polynomial ac_i2a1p = integral(expr_a1p, {2, {1, 3}});
    const po::polynomial ex_i2a1p{{4, {1, 2,    1}}};

    PO_ASSERT(compare::unordered_equal_terms(ac_i2a1p, ex_i2a1p), ac_i2a1p);

    PO_ASSERT(ac_i2a1p.rank() == 3, ac_i2a1p.rank());
    PO_ASSERT(ac_i2a1p.degree() == 4, ac_i2a1p.degree());
    PO_ASSERT(compare::equal(ac_i2a1p.degrees(), {1, 2, 1}), ac_i2a1p.degrees());

    PO_LINE;
  }
}

