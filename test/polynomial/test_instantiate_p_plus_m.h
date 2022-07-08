#include "../../polynomial.h"

#include <cassert>

void test_instantiate_p_plus_m()
{
  {
    po::polynomial p{{6, {0}}};
    po::monomial m{{6, {3}}};

    po::polynomial r = po::instantiate(p + m, po::rank<1>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {6, {0}},
        {6, {3}}
      }),
      r);

    assert(r(7.3) == p(7.3) + m(7.3));
  }

  PO_LINE;
}