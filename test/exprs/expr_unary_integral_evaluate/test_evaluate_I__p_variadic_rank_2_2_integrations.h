#include "../../../ostream/valarray_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_I__p_variadic_rank_2_2_integrations()
{
  /*
   * I0(I1(p))
   */
  {
    po::polynomial p     {{ 2, {1, 0}}};

    const double ex = 1.;


    // TODO These 2 are ugly.
    // const double ac = instantiate(integral(p, po::parametric_interval{0, {0, 1}}, po::parametric_interval{0, {0, 1}}))();
    const double ac = instantiate(
      integral(
        p,
        po::parametric_interval{0, {0, 1}},
        po::parametric_interval{0, {0, 1}})
      )();

    // TODO Want this instead:
    // const auto ex = integral(p, {0, {0, 1}}, {0, {0, 1}});
    // const double ac = instantiate(integral(p, {0, {0, 1}}, {0, {0, 1}}));
    // const double ac = instantiate(integral(p,
      // {0, {0, 1}},
      // {0, {0, 1}}));

    PO_ASSERT(ac == ex, ac);
  }

  /*
   * I1(I0(p))
   */
  {
    po::polynomial p     {{ 2, {1, 0}}};

    const double ex = 1.;
    const double ac = instantiate(integral(p, po::parametric_interval{1, {0, 1}}, po::parametric_interval{0, {0, 1}}))();

    PO_ASSERT(ac == ex, ac);
  }

  /*
   * I0(I1(p))
   */
  {
    po::polynomial p     {{ 3.7, {1, 0}}};

    const double ex = 1.85;
    const double ac = instantiate(
      integral(p,
        po::parametric_interval{0, {0, 1}},
        po::parametric_interval{0, {0, 1}})
      )();

    const auto iip = instantiate(integral(p, po::parametric_interval{0, {0, 1}}, po::parametric_interval{0, {0, 1}}));

    assert(iip.rank() == 0);
    assert(iip.degree() == 0);
    assert(iip.degrees().size() == 0);

    PO_ASSERT(ac == ex, ac);
  }

  /*
   * I0(I1(p))
   */
  {
    po::polynomial p     {{ 3.7, {1, 1}}};

    const double ex = 0.925;
    const double ac = instantiate(
      integral(p,
        po::parametric_interval{0, {0, 1}},
        po::parametric_interval{0, {0, 1}})
      )();

    const auto iip = instantiate(integral(p, po::parametric_interval{0, {0, 1}}, po::parametric_interval{0, {0, 1}}));

    PO_ASSERT(ac == ex, ac);
  }

  /*
   * I0(I1(p))
   */
  {
    po::polynomial p     {{ 3.7, {1, 1}}};

    const double ex = 0.925;
    const double ac = instantiate(
      integral(p,
        po::parametric_interval{0, {0, 1}},
        po::parametric_interval{0, {0, 1}})
      )();

    PO_ASSERT(ac == ex, ac);
  }

  PO_LINE;
}
