#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_A__p_variadic_rank_4_2As()
{
  /*
   * A0(A0(p))
   */
  {
    po::polynomial p{{ 3.7, {1, 0, 5, 0}}, {-2.01, {4, 2, 3, 7}}};

    const auto aap = instantiate(antiderivative(p, 0, 0));

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {3.7 / 2 / 3  , {3, 0, 5, 0}},
        {-2.01 / 5 / 6, {6, 2, 3, 7}},
      }),
      aap);

    assert(aap.rank() == 4);
    assert(aap.degree() == 18);
    assert(compare::equal(aap.degrees(), {6, 2, 5, 7}));

    PO_LINE;
  }

  {
    po::polynomial p{{ 3.7, {1, 0, 5, 0}}, {-2.01, {4, 2, 3, 7}}};

    const auto aap = instantiate(antiderivative(p, 1, 2));

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {3.7 / 6      , {1, 1, 6, 0}},
        {-2.01 / 3 / 4, {4, 3, 4, 7}},
      }),
      aap);

    assert(aap.rank() == 4);
    assert(aap.degree() == 18);
    assert(compare::equal(aap.degrees(), {4, 3, 6, 7}));

    PO_LINE;
  }


}