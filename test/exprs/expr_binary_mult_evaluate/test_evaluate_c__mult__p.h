#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_c__mult__p()
{
  {
    po::polynomial p{};
    auto x = -4 * p;
    assert(x.expr1.expr1 == -4);

    PO_LINE;
  }

  {
    po::polynomial p{};
    auto x = 3ull * p;

    assert(x.expr1.expr1 == 3);

    PO_LINE;
  }

  {
    po::polynomial p{po::rank<7>{}};
    auto x = 2*p;
    assert(x(1, 1, 1, 1, 1, 1, 1) == 0.);
    assert(x(0, 3, 2, 3, 7, 0, 2) == 0.);

    PO_LINE;
  }

  {
    po::polynomial p{po::rank<7>{}};
    assert((2*p)(1, 1, 1, 1, 1, 1, 1) == 0.);
    assert((2*p)(0, 3, 2, 3, 7, 0, 2) == 0.);

    PO_LINE;
  }


  {
    po::polynomial p{{3.2, {4, 5, 3, 5, 2}}};
    po::scalar_type c = 5;
    auto x = c * p;

    assert(x.expr1.expr1 == c);

    assert(x(1, 1, 1, 1, 1) == 16.);

    PO_LINE;
  }
}