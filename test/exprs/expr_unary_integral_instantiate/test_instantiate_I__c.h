#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_I__c()
{
  {
    const auto x = po::integral(po::expr_constant{6.}, {5, {3, 6}});

    assert(x.place == 5);
    assert(x.a == 3);
    assert(x.b == 6);

    po::polynomial p = instantiate(x, po::rank<0>{});

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {18., {}},
      }),
      p);

    PO_LINE;
  }

  {
    const auto x = po::integral(7.2, {5, {3, 6}});

    assert(x.place == 5);
    assert(x.a == 3);
    assert(x.b == 6);

    po::polynomial p = instantiate(x, po::rank<0>{});

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {21.6, {}},
      }),
      p);

    PO_LINE;
  }

}
