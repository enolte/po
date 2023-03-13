#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_c__plus__p()
{
  {
    po::polynomial p{{0, {0}}};

    auto x = -4 + p;

    assert(x(7.3) == -4);
  }

  {
    po::polynomial p{{0, {0}}};
    assert((-4 + p)(7.3) == -4);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    assert((c + p)(3) == c);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    assert((c + c + p)(3) == c + c);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    assert((c + c + p)(3) == c + c);
  }

  {
    const po::polynomial p{{4, {0, 4, 3}}};
    po::scalar_type c = 5;

    assert(((c + c) + p)(3, 2, 1) == (4 * 1 * 16 * 1) + 5 + 5);
    assert((c + (c + p))(3, 2, 1) == (4 * 1 * 16 * 1) + 5 + 5);
    assert((c + c + p)(3, 2, 1) == (4 * 1 * 16 * 1) + 5 + 5);
  }

  PO_LINE;
}
