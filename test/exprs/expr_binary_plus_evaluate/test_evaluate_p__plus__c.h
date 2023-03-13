#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_p__plus__c()
{
  {
    po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((p + c + c)(3) == c + c);
  }

  {
    const po::polynomial p{{0, {0}}};
    po::scalar_type c = 5;

    assert((p + c + c)(3) == c + c);
  }

  {
    const po::polynomial p{{4, {0, 4, 3}}};
    po::scalar_type c = 5;

    assert((p + c + c)(3, 2, 1) == (4 * 1 * 16 * 1) + 5 + 5);
  }

  PO_LINE;
}
