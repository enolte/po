#include "../../polynomial.h"

#include "../../evaluate/evaluate_gH.h"

void test_evaluate_gH()
{
  {
    po::polynomial p{};
    assert(p.rank() == 0);
    po::evaluate_gH(p);
    assert(po::evaluate_gH(p) == 0);
  }

  {
    po::polynomial p{po::rank<0>{}};
    assert(po::evaluate_gH(p) == 0);
  }

  {
    po::polynomial p{0, po::rank<0>{}};
    assert(po::evaluate_gH(p, 0) == 0);
  }

  {
    const auto p = po::polynomial::make_zero(0);
    assert(p.rank() == 0);
    assert(po::evaluate_gH(p, 0) == 0);
  }

  {
    po::polynomial p{po::rank<6>{}};
    assert(po::evaluate_gH(p, 3, 2.3, -0.7, 3, 13.65, 5) == 0.);
  }

  {
    po::polynomial p{7.5, po::rank<6>{}};
    assert(po::evaluate_gH(p, 3, 2.3, -0.7, 3, 13.65, 5) == 7.5);
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}}
    });

    assert(po::evaluate_gH(p, 3, 2, 1) == 0.);

  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(po::evaluate_gH(p, 3, 2, 1) == 7.5);

  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0, 7, 4, 1, 1, 7}},
      {-4 , {1, 1, 0, 5, 4, 1, 0, 0}},
      {-3 , {0, 0, 0, 0, 0, 3, 0, 0}},
    });

    assert(
      po::evaluate_gH(p,
          1.5,    1,  2,  1,   2.5,     2,  3,    2) ==
      1 * 3.375 * 1 * 1 * 1 * 39.0625 * 2 * 3 * 128   +
     -4 * 1.5   * 1 * 1 * 1 * 39.0625 * 2 * 1 *   1   +
     -3 * 1     * 1 * 1 * 1 *  1      * 8 * 1 *   1);
  }

  {
    po::polynomial p
    ({
      { 1. , {3, 0, 0}},
      {-4  , {1, 1, 0}},
      { 3. , {0, 0, 2}},
      {-3  , {0, 0, 0}},
      { 2.5, {1, 0, 0}}
    });

    PO_ASSERT(
      po::evaluate_gH(p, 3,2,1) ==
      1   * 27 * 1 * 1   +
     -4   *  3 * 2 * 1   +
      3   *  1 * 1 * 1   +
     -3   *  1 * 1 * 1   +
      2.5 *  3 * 1 * 1,
      p);
  }

  {
    po::polynomial p
    ({
      {-6. , {0, 5, 2}},
      { 1. , {3, 0, 0}},
      {-4  , {1, 1, 0}},
      { 3. , {0, 0, 2}},
      {-3  , {0, 0, 0}},
      { 2.5, {1, 0, 0}}
    });

    assert(
      po::evaluate_gH(p, 3,2,1) ==
     -6   *  1 *32 * 1   +
      1   * 27 * 1 * 1   +
     -4   *  3 * 2 * 1   +
      3   *  1 * 1 * 1   +
     -3   *  1 * 1 * 1   +
      2.5 *  3 * 1 * 1);
  }

  PO_LINE;
}


