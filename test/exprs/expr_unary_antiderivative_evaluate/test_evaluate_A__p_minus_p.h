#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_evaluate_A__p_minus_p_different_ranks();

void test_evaluate_A__p_minus_p()
{
  // lvalues, difference == 0, place in range, test 1
  {
    const double ex = 0.;

    po::polynomial p
    {
      { 3, {1, 1}},
    };

    po::polynomial q
    {
      { 3, {1, 1}},
    };

    double ac;
    ac = po::antiderivative(p - q, 0)(16, -14.5411);
    assert(ac == ex);
    ac = po::antiderivative(p - q, 0)(-2.015, 11.04);
    assert(ac == ex);
    ac = po::antiderivative(p - q, 0)(-77.450, .3564);
    assert(ac == ex);

    PO_LINE;
  }

  // lvalues, difference == 0, place in range, test 2
  {
    const double ex = 0.;

    po::polynomial p
    {
      { 3, {1, 1}},
    };

    po::polynomial q
    {
      { 3, {1, 1}},
    };

    double ac;
    ac = po::antiderivative(p - q, 1)(16, -14.5411);
    assert(ac == ex);
    ac = po::antiderivative(p - q, 1)(-2.015, 11.04);
    assert(ac == ex);
    ac = po::antiderivative(p - q, 1)(-77.450, .3654);
    assert(ac == ex);

    PO_LINE;
  }

  // lvalues, difference == 0, place OOR
  {
    const double ex = 0.;

    po::polynomial p
    {
      { 3, {1, 1}},
    };

    po::polynomial q
    {
      { 3, {1, 1}},
    };

    double ac;
    ac = po::antiderivative(p - q, 5)(16, -14.5411, 43, 2., 4.1, 4.0932);
    assert(ac == ex);
    ac = po::antiderivative(p - q, 5)(-2.015, 11.04, 33, -2.2, 0.0015, -5.0234);
    assert(ac == ex);
    ac = po::antiderivative(p - q, 5)(-77.450, .3564, 33, 11, 909998.4, 34.21354);
    assert(ac == ex);

    PO_LINE;
  }

  // lvalues, difference != 0, place in range, test 1
  {
    po::polynomial p
    {
      { 3, {1, 1}},
    };

    po::polynomial q
    {
      { 2, {1, 1}},
    };

    enum : po::rank_type { place = 0 };

    double ac;

    ac = po::antiderivative(p - q, place)(1, 1);
    assert(ac == 0.5);

    ac = po::antiderivative(p - q, place)(-2.015, 1);
    assert(near_rel(ac, 0.5*-2.015*-2.015, 0x1p-51));

    ac = po::antiderivative(p - q, place)(-77.450, 1);
    assert(near_rel(ac, 0.5*-77.450*-77.450, 0x1p-51));

    PO_LINE;
  }

  // lvalues, difference != 0, place in range, test 2
  {
    po::polynomial p
    {
      { 3  , {1, 1, 4, 2}},
    };

    po::polynomial q
    {
      { 2.2, {1, 7, 8, 1}},
      {-4  , {1, 0, 0, 12}},
    };

    enum : po::rank_type { place = 2 };

    double ac, ex;
    ac = po::antiderivative(p - q, place)(1, 1, 1, 1);
    ex = 3./5 - 2.2/9 + 4;

    assert(ac == ex);

    ac = po::antiderivative(p - q, place)(-2.015, 1, 2, 2);
    ex = 3./5 * -2.015 * 1 * 2*2*2*2*2 * 2*2
       -(
          2.2/9 * -2.015 * 1 * 2*2*2*2*2*2*2*2*2 * 2
          +
          -4.* -2.015 * 1 * 2 * 2*2*2*2*2*2*2*2*2*2*2*2
        );
    assert(ac == ex);

    ac = po::antiderivative(p - q, place)(-77.450, 1, 2, 1);
    ex = 3./5 * -77.45 * 1 * 2*2*2*2*2 * 1
       -(
          2.2/9 * -77.45 * 1 * 2*2*2*2*2*2*2*2*2 * 1
          +
          -4 * -77.45 * 1 * 2 * 1
        );
    assert(near_rel(ac, ex, 0x1p-51));

    PO_LINE;
  }

  // rvalues, difference != 0, place in range
  {
    using P = po::polynomial;
    enum : po::rank_type { place = 0 };

    double ac, ex;
    ac = po::antiderivative(P{{ 3, {1, 1}}} - P{{ 2, {2, 1}}}, place)(1, 1);
    assert(ac == 3./2 - 2./3);

    ac = po::antiderivative(P{{ 3, {1, 1}}} - P{{ 2, {2, 1}}}, place)(-2.015, 1);
    ex = 3./2*-2.015*-2.015 - 2./3*-2.015*-2.015*-2.015;
    assert(near_rel(ac, ex, 0x1p-51));

    ac = po::antiderivative(P{{ 3, {1, 1}}} - P{{ 2, {2, 1}}}, place)(-77.450, 1);
    ex = 3./2*-77.450*-77.450 - 2./3*-77.450*-77.450*-77.450;
    assert(near_rel(ac , ex, 0x1p-52));

    PO_LINE;
  }

  // rvalues, difference != 0, place OOR
  {
    using P = po::polynomial;
    enum : po::rank_type { place = 7 };

    double ac, ex;
    ac = po::antiderivative(P{{ 3, {1, 1}}} - P{{ 2, {2, 1}}}, place)(1, 1, 1, 1, 1, 1, 1, 3);
    ex = 3*3 - 2*3;
    assert(ac == ex);

    ac = po::antiderivative(P{{ 3, {1, 1}}} - P{{ 2, {2, 1}}}, place)(-2.015, 1, 1, 1, 1, 1, 1, 3);
    ex = 3*-2.015*3 - 2*-2.015*-2.015*3;
    assert(ac == ex);

    ac = po::antiderivative(P{{ 3, {1, 1}}} - P{{ 2, {2, 1}}}, place)(-77.450, 1, 1, 1, 1, 1, 1, 3);
    ex = 3*-77.450*3 - 2*-77.450*-77.450*3;
    assert(ac == ex);

    PO_LINE;
  }

  test_evaluate_A__p_minus_p_different_ranks();
}


void test_evaluate_A__p_minus_p_different_ranks()
{
  // subexprs with incompatble ranks
  {
    po::polynomial p
    {
      { 3, {1, 1, 7}},
    };

    po::polynomial q
    {
      { 3, {1, 1}},
    };

    double ac;
    ac = po::antiderivative(p - q, 0)(16, -14.5411, 3.4);
    assert(ac != ac);
    ac = po::antiderivative(p - q, 0)(-2.015, 11.04, -0.0015);
    assert(ac != ac);
    ac = po::antiderivative(p - q, 0)(-77.450, .3564, 12.50685);
    assert(ac != ac);

    PO_LINE;
  }
}