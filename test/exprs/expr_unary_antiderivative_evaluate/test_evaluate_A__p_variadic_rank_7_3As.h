#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_A__p_variadic_rank_7_3As()
{
  /*
   * A0(A0(A0(p))), all in range
   */
  {
    po::polynomial p{{ 3.7, {1, 0, 5, 2, 0, 0, 8}}, {-2.01, {4, 2, 3, 5, 4, 7, 7}}};

    const auto aap = instantiate(antiderivative(p, 0, 0, 0));

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {3.7 / 2 / 3 / 4  , {4, 0, 5, 2, 0, 0, 8}},
        {-2.01 / 5 / 6 / 7, {7, 2, 3, 5, 4, 7, 7}},
      }),
      aap);

    assert(aap.rank() == 7);
    assert(aap.degree() == 35);
    assert(compare::equal(aap.degrees(), {7, 2, 5, 5, 4, 7, 8}));

    PO_LINE;
  }

  /*
   * A0(A0(A0(p))), all in range, test 2
   */
  {
    po::polynomial p{{ 3.7, {1, 0, 5, 2, 0, 0, 8}}, {-2.01, {4, 2, 3, 5, 4, 7, 7}}};

    const auto aap = instantiate(antiderivative(p, 6, 1, 2));

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {3.7 / 9 / 6      , {1, 1, 6, 2, 0, 0, 9}},
        {-2.01 / 8 / 3 / 4, {4, 3, 4, 5, 4, 7, 8}},
      }),
      aap);

    assert(aap.rank() == 7);
    assert(aap.degree() == 35);
    assert(compare::equal(aap.degrees(), {4, 3, 6, 5, 4, 7, 9}));

    PO_LINE;
  }

  /*
   * A9(A11(A3(p))), 2 OOR
   */
  {
    po::polynomial p{{ 3.7, {1, 0, 5, 2, 0, 0, 8}}, {-2.01, {4, 2, 3, 5, 4, 7, 7}}};

    const auto aap = instantiate(antiderivative(p, 3, 11, 9));

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {3.7 / 3          , {1, 0, 5, 3, 0, 0, 8, 0, 0, 1, 0, 1}},
        {-2.01 / 6        , {4, 2, 3, 6, 4, 7, 7, 0, 0, 1, 0, 1}},
      }),
      aap);

    assert(aap.rank() == 12);
    assert(aap.degree() == 35);
    assert(compare::equal(aap.degrees(), {4, 2, 5, 6, 4, 7, 8, 0, 0, 1, 0, 1}));

    PO_LINE;
  }

}