#include "../../../ostream/valarray_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

#include "../expr_unary_integral_evaluate/I.h"

void test_instantiate_D__IDp()
{
  {
    po::polynomial p        {{2, {1, 1, 1, 1}}};
//  po::polynomial dp1      {{2, {1, 0, 1, 1}}}; // D(p, 1)
//  po::polynomial dp1_2_13 {{8, {1, 0,    1}}}; // I(D(p, 1)) over [1, 3] in place 2
    po::polynomial ex       {{0, {1, 0,    1}}}; // D(I(D(p, 1) over [1, 3] in place 2), 1)

    const po::polynomial ac = instantiate(D(I(D(p, 1), {2, {1, 3}}), 1));

    assert(compare::unordered_equal_terms(
      ac,
      {
        {0, {1, 0, 1}}
      }));

    assert(ac.rank() == 3);
    PO_ASSERT(ac.degree() == 2, ac.degree());
    assert(compare::equal(ac.degrees(), {1, 0, 1}));

    PO_ASSERT(ex == ac, ac);
  }

  {
    po::polynomial p        {{2, {1, 1, 1, 1}}};
//  po::polynomial dp1      {{2, {1, 0, 1, 1}}}; // D(p, 1)
//  po::polynomial dp1_2_13 {{8, {1, 0,    1}}}; // I(D(p, 1)) over [1, 3] in place 2
    po::polynomial ex       {{8, {1, 0,    0}}}; // D(I(D(p, 1) over [1, 3] in place 2), 2)

    const po::polynomial ac = instantiate(D(I(D(p, 1), {2, {1, 3}}), 2));

    assert(compare::unordered_equal_terms(
      ac,
      {
        {8, {1, 0, 0}}
      }));

    assert(ac.rank() == 3);
    PO_ASSERT(ac.degree() == 1, ac.degree());
    assert(compare::equal(ac.degrees(), {1, 0, 0}));

    PO_ASSERT(ex == ac, ac);
  }

  PO_LINE;
}
