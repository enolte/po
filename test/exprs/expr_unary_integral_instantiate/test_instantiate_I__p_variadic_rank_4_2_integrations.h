#include "../../../ostream/valarray_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_I__p_variadic_rank_4_2_integrations()
{
  using place = po::parametric_interval;

  /*
   * I0(I2(p))
   */
  {
    po::polynomial p     {{7 , {1, 0, 0, 5}}};

    const auto iip = instantiate(po::integral(p, place{2, {1, 3}}, place{0, {1, 2}}));

    PO_ASSERT(compare::unordered_equal_terms(
      iip,
      {
        {7. * (3-1)/2 * 3, {0, 5}}
      }),
      iip);

    assert(iip.rank() == 2);
    assert(iip.degree() == 5);
    assert(compare::equal(iip.degrees(), {0, 5}));
  }
}

