#include "../../ostream/valarray_ostream.h"

#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_expr_integral_p_evaluate()
{
  {
    po::polynomial q     {{ 2, {1, 0}}};
    po::polynomial Q2_13 {{ 4, {1, 0}}};  // integral over [1, 3] in place 7 >= rank(q)

    const double ex = Q2_13(2, 1);
    const double ac = po::integral(q, {7, {1, 3}})(2, 1);

    assert(ac == ex);
  }

  {
    po::polynomial q     {{ 7, {1, 0, 0, 5}}};
    po::polynomial Q2_13 {{14, {1, 0, 0, 5}}};  // integral over [1, 3] in place 7 >= rank(q)

    const double ex = Q2_13(3, 2, 1, 1);
    const double ac = po::integral(q, {7, {1, 3}})(3, 2, 1, 1);

    assert(ac == ex);
  }

  {
    po::polynomial q     {{7  , {1, 0, 3, 5}}};
    po::polynomial Q2_13 {{14 , {1, 0, 3, 5}}};  // integral over [1, 3] in place 7 >= rank(q)

    const double ex = Q2_13(3, 2, 1, 1);
    const double ac = po::integral(q, {7, {1, 3}})(3, 2, 1, 1);

    assert(ac == ex);
  }

  {
    po::polynomial q     {{7 , {1, 0, 0, 5}}};
    po::polynomial Q2_13 {{14, {1, 0,    5}}};  // integral over [1, 3] in place 2

    const double ex = Q2_13(3, 2, 1);
    const double ac = po::integral(q, {2, {1, 3}})(3, 2, 1);

    assert(ac == ex);
  }

  {
    po::polynomial p     {{2, {1, 1, 1, 1}}};
    po::polynomial P2_13 {{8, {1, 1,    1}}}; // integral over [1, 3] in place 2

    const double ex = P2_13(3, 2, 1);
    const double ac = po::integral(p, {2, {1, 3}})(3, 2, 1);

    assert(ac == ex);
  }

  {
    po::polynomial p     {{2, {1, 1, 1, 1}}};
    po::polynomial P2_13 {{8, {1, 1,    1}}}; // integral over [1, 3] in place 2

    const double ex = P2_13(3, 2, 1);
    const double ac = po::integral(p, 2, {1, 3})(3, 2, 1);

    assert(ac == ex);
  }

  {
    po::polynomial p     {{2, {1, 1, 1, 1}}};
    po::polynomial P2_13 {{8, {1, 1,    1}}}; // integral over [1, 3] in place 2

    const double ex = P2_13(3, 2, 1);

    const auto x = po::integral(p, 2, {1, 3});
    const double ac = x(3, 2, 1);

    assert(ac == ex);
  }

  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = integral(p, 0, 0, 1);
    PO_ASSERT(x(3, 5) == 3*5, x(3, 5));
  }

  {
    po::polynomial p{{2, {1, 2, 3}}};
    auto x = integral(p, 1, {0, 1});
    PO_ASSERT(x(3, 5) == (2./3)*3*5*5*5, x(3, 5));
  }

  {
    po::polynomial p     {{2, {1, 1, 1, 1}}, { 3  , {0, 4, 1, 0}}};
    po::polynomial P2_01 {{1, {1, 1,    1}}, { 1.5, {0, 4,    0}}}; // integral over [0, 1] in place 2
//  po::polynomial P2_13 {{8, {1, 1,    1}}, {12  , {0, 4,    0}}}; // integral over [1, 3] in place 2

    const double ex = P2_01(3, 2, 1);
    const double ac = po::integral(p, 2, {0, 1})(3, 2, 1);

    assert(ac == ex);
  }

  {
    po::polynomial p     {{2, {1, 1, 1, 1}}, { 3  , {0, 4, 1, 0}}};
//  po::polynomial P2_01 {{1, {1, 1,    1}}, { 1.5, {0, 4,    0}}}; // integral over [0, 1] in place 2
    po::polynomial P2_13 {{8, {1, 1,    1}}, {12  , {0, 4,    0}}}; // integral over [1, 3] in place 2

    const double ex = P2_13(3, 2, 1);
    const double ac = po::integral(p, 2, {1, 3})(3, 2, 1);

    assert(ac == ex);
  }

  {
    po::polynomial p     {{2, {1, 1, 1, 1}}, { 3, {0, 4, 2, 0}}};
//  po::polynomial A2    {{1, {1, 1, 2, 1}}, { 1, {0, 4, 3, 0}}}; // primitive antiderivative in place 2
    po::polynomial P2_01 {{1, {1, 1,    1}}, { 1, {0, 4,    0}}}; // integral over [0, 1] in place 2
    po::polynomial P2_13 {{8, {1, 1,    1}}, {26, {0, 4,    0}}}; // integral over [1, 3] in place 2

    assert(po::integral(p, 2, {0, 1})(1, 3, -1.3) == P2_01(1, 3, -1.3));
    PO_ASSERT(po::integral(p, 2, {1, 3})(1, 3, -1.3) == P2_13(1, 3, -1.3), P2_13(1, 3, -1.3));
  }


  {
    po::polynomial p     {{2, {1, 1, 1, 1}}};
    po::polynomial P2_13 {{8, {1, 1,    1}}}; // integral over [1, 3] in place 2
    const auto Ip = po::integral(p, 2, {1, 3});
    const po::polynomial ip = po::instantiate(Ip);

    assert(ip(3, 2, 1) == P2_13(3, 2, 1));
    assert(ip(3, 2, 1) == 48);
  }

  PO_LINE;
}
