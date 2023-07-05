#include "../../polynomial.h"

void test_evaluate_naive()
{
  {
    po::polynomial p{};
    assert(po::evaluate_naive(p) == 0);

    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_zero(po::rank<0>{})};
    assert(po::evaluate_naive(p) == 0);

    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_constant(po::rank<0>{}, 0)};
    assert(po::evaluate_naive(p) == 0);

    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_constant(po::rank<0>{}, 7.5)};
    assert(po::evaluate_naive(p) == 7.5);

    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_zero(po::rank<6>{})};
    assert(po::evaluate_naive(p, 3, 2.3, -0.7, 3, 13.65, 5) == 0.);

    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_constant(po::rank<6>{}, 7.5)};
    assert(po::evaluate_naive(p, 3, 2.3, -0.7, 3, 13.65, 5) == 7.5);

    PO_LINE;
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}}
    });

    PO_ASSERT(po::evaluate_naive(p, 3,2,1) == 0., po::evaluate_naive(p, 3, 2, 1));

    PO_LINE;
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    });

    PO_ASSERT(po::evaluate_naive(p, 3,2,1) == 7.5, p(3,2,1));

    PO_LINE;
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0, 7, 4, 1, 1, 7}},
      {-4 , {1, 1, 0, 5, 4, 1, 0, 0}},
      {-3 , {0, 0, 0, 0, 0, 3, 0, 0}},
    });

    PO_ASSERT(
      po::evaluate_naive(p,  1.5,    1,  2,  1,   2.5,     2,  3,    2) ==
        1 * 3.375 * 1 * 1 * 1 * 39.0625 * 2 * 3 * 128   +
       -4 * 1.5   * 1 * 1 * 1 * 39.0625 * 2 * 1 *   1   +
       -3 * 1     * 1 * 1 * 1 *  1      * 8 * 1 *   1,
     po::evaluate_naive(p, 1.5,  1,  2,  1,   2.5,     2,  3,    2));

    PO_LINE;
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
      po::evaluate_naive(p,3,2,1) ==
        1   * 27 * 1 * 1   +
       -4   *  3 * 2 * 1   +
        3   *  1 * 1 * 1   +
       -3   *  1 * 1 * 1   +
        2.5 *  3 * 1 * 1,
      p);

    PO_LINE;
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
      po::evaluate_naive(p,3,2,1) ==
       -6   *  1 *32 * 1   +
        1   * 27 * 1 * 1   +
       -4   *  3 * 2 * 1   +
        3   *  1 * 1 * 1   +
       -3   *  1 * 1 * 1   +
        2.5 *  3 * 1 * 1);

    PO_LINE;
  }
}


