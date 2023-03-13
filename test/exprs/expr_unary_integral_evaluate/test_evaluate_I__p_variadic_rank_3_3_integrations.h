#include "../../../ostream/valarray_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_I__p_variadic_rank_3_3_integrations()
{
  /*
   * I2(I1(I0(p)))
   */
  {
    po::polynomial p     {{ 2, {1, 0, 0}}};

    const double ex = 1.;

    const double ac = instantiate(
      integral(
        p,
        po::parametric_interval{0, {0, 1}},
        po::parametric_interval{0, {0, 1}},
        po::parametric_interval{0, {0, 1}})
      )();

    PO_ASSERT(ac == ex, ac);
  }

  /*
   * I0(I2(I1(p)))
   */
  {
    po::polynomial p     {{ 2, {1, 0, 0}}};

    const double ex = 1.;
    const double ac = instantiate(
      integral(
        p,
        po::parametric_interval{1, {0, 1}},
        po::parametric_interval{1, {0, 1}},
        po::parametric_interval{0, {0, 1}}))();

    PO_ASSERT(ac == ex, ac);
  }


  PO_LINE;
}
