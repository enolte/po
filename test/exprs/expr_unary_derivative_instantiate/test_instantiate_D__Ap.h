#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

#include "../expr_unary_antiderivative_evaluate/A.h"

void test_instantiate_D__Ap()
{
  {
    po::polynomial p        {{2, {1, 1, 1, 1}}};
    po::polynomial d2a1p    {{1, {1, 2, 0, 1}}};

    const po::polynomial ac = D(A(p, 1), 2);

    PO_ASSERT(compare::unordered_equal_terms(ac, d2a1p), ac);

    assert(ac.rank() == 4);
    PO_ASSERT(ac.degree() == 4, ac.degree());
    assert(compare::equal(ac.degrees(), {1, 2, 0, 1}));

    PO_ASSERT(ac == d2a1p, ac);

    PO_LINE;
  }

  {
    po::polynomial p        {{2  , {1, 3, 1, 1}}, {4.3  , {3, 2, 1, 2}}};
    po::polynomial d3a1p    {{0.5, {1, 4, 1, 0}}, {8.6/3, {3, 3, 1, 1}}};

    const po::polynomial ac = instantiate(D(A(p, 1), 3));

    PO_ASSERT(compare::unordered_equal_terms(ac, d3a1p), ac);

    assert(ac.rank() == 4);
    PO_ASSERT(ac.degree() == 8, ac.degree());
    assert(compare::equal(ac.degrees(), {3, 4, 1, 1}));

    PO_LINE;
  }

}
