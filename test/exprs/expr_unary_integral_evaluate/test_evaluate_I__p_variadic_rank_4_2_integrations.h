#include "../../../ostream/valarray_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_I__p_variadic_rank_4_2_integrations()
{
  using place = po::parametric_interval;

  /*
   * I0(I2(p))
   */
  {
    po::polynomial p     {{7 , {1, 0, 0, 5}}};

    const double ex = 21*32;
    const double ac = integral(p, place{2, {1, 3}}, place{0, {1, 2}})(1.5, 2);

    assert(ac == ex);
  }
}

