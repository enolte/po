#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_A__p_variadic_rank_3_2As()
{
  /*
   * A0(A0(p))
   */
  {
    po::polynomial p{{ 3.7, {1, 0, 0}}};

    const auto aap = instantiate(antiderivative(p, 0, 0));

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {3.7 / 2 / 3, {3, 0, 0}}
      }),
      aap);

    assert(aap.rank() == 3);
    assert(aap.degree() == 3);
    assert(compare::equal(aap.degrees(), {3, 0, 0}));

    PO_LINE;
  }

  /*
   * A1(A1(p)), test 2: different places
   */
  {
    po::polynomial p{{ 3.7, {1, 0, 0}}};

    const auto aap = instantiate(antiderivative(p, 1, 0));

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {3.7 / 2, {2, 1, 0}}
      }),
      aap);

    assert(aap.rank() == 3);
    assert(aap.degree() == 3);
    assert(compare::equal(aap.degrees(), {2, 1, 0}));

    PO_LINE;
  }

  /*
   * A1(A1(p)), test 3: permuting places in test s
   */
  {
    po::polynomial p{{ 3.7, {1, 0, 0}}};

    const auto aap = instantiate(antiderivative(p, 0, 1));

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {3.7 / 2, {2, 1, 0}}
      }),
      aap);

    assert(aap.rank() == 3);
    assert(aap.degree() == 3);
    assert(compare::equal(aap.degrees(), {2, 1, 0}));

    PO_LINE;
  }

  /*
   * A0(A1(p))
   */
  {
    po::polynomial p{{ 3.7, {1, 0, 0}}};

    const auto aap = instantiate(antiderivative(p, 1, 0));

    PO_ASSERT(compare::unordered_equal_terms(
      aap,
      {
        {3.7/2, {2, 1, 0}}
      }),
      aap);

    assert(aap.rank() == 3);
    assert(aap.degree() == 3);
    assert(compare::equal(aap.degrees(), {2, 1, 0}));

    PO_LINE;
  }
}