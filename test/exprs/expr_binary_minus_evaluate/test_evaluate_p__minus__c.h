#include "../../../polynomial.h"
#include "../../macros.h"
#include <cassert>

void test_evaluate_p__minus__c()
{
  {
    po::polynomial p{{0, {0}}};
    auto x = p - -4;

    assert(x.expr2.expr1 == -4);
    assert(x(8) == 4);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;
    auto x = p - c;

    assert(x.expr2.expr1 == c);
    assert(x(8) == -5);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((p - c)(9.234) == -5);
  }

  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((p - c - c)(3) == -c - c);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((p - c - c)(3) == -c - c);
  }

  {
    const po::polynomial p{{4, {0, 4, 3}}};
    po::scalar_type c = 5;

    assert((p - c - c)(3, 2, 1) == (4 * 1 * 16 * 1) - 5 - 5);
  }

  PO_LINE;
}

