#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_I__p_variadic_rank_3_3_integrations()
{
  /*
   * I1(I2(I0(p)))
   */
  {
    po::polynomial p     {{ 3.7, {1, 0, 0}}};

    const double ex = 1.85;

    const auto iiip = instantiate(
      integral(
        p,
        po::parametric_interval{1, {0, 1}},
        po::parametric_interval{1, {0, 1}},
        po::parametric_interval{0, {0, 1}}));

    assert(iiip.rank() == 0);
    assert(iiip.degree() == 0);
    assert(iiip.degrees().size() == 0);

    const double ac = iiip();

    PO_ASSERT(ac == ex, ac);

    PO_LINE;
  }

}
