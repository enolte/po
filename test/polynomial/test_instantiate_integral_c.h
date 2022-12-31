#include "../../ostream/valarray_ostream.h"

#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_instantiate_integral_c()
{
  {
    const auto x = po::integral(po::expr_constant{6.}, {5, {3, 6}});

    assert(x.place == 5);
    assert(x.a == 3);
    assert(x.b == 6);

    po::polynomial p = instantiate(x, po::rank<0>{});

    PO_ASSERT(unordered_equal(
      p.terms,
      {
        {18., {}},
      }),
      p);
  }

  {
    const auto x = po::integral(7.2, {5, {3, 6}});

    assert(x.place == 5);
    assert(x.a == 3);
    assert(x.b == 6);

    po::polynomial p = instantiate(x, po::rank<0>{});

    PO_ASSERT(unordered_equal(
      p.terms,
      {
        {21.6, {}},
      }),
      p);
  }


  PO_LINE;
}
