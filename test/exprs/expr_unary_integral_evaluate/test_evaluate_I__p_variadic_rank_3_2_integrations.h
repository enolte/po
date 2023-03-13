#include "../../../ostream/valarray_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_I__p_variadic_rank_3_2_integrations()
{
  /*
   * I2(I1(p))
   */
  {
    po::polynomial p     {{ 3.7, {1, 0, 0}}};

    const auto iip = instantiate(
      integral(
        p,
        po::parametric_interval{1, {0, 1}},
        po::parametric_interval{1, {0, 1}}));

    PO_ASSERT(compare::unordered_equal_terms(
      iip,
      {
        {3.7, {1}}
      }),
      iip);

    assert(iip.rank() == 1);
    assert(iip.degree() == 1);
    assert(compare::equal(iip.degrees(), {1}));
  }

  /*
   * I0(I1(p))
   */
  {
    po::polynomial p     {{ 3.7, {1, 0, 0}}};

    const auto iip = instantiate(
      integral(
        p,
        po::parametric_interval{1, {0, 1}},
        po::parametric_interval{0, {0, 1}}));

    PO_ASSERT(compare::unordered_equal_terms(
      iip,
      {
        {1.85, {0}}
      }),
      iip);

    assert(iip.rank() == 1);
    assert(iip.degree() == 0);
    assert(compare::equal(iip.degrees(), {0}));
  }
}