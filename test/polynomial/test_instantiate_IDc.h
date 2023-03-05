#include "../../ostream/valarray_ostream.h"

#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_instantiate_IDc()
{
  {
    const auto x = po::D(-3.7, 1);

    const po::polynomial ac = instantiate(integral(x, {2, {1, 3}}));

    PO_ASSERT(unordered_equal_terms(
      ac,
      {
        {0, {}}
      }),
      ac);

    PO_ASSERT(ac.rank() == 0, ac.rank());
    PO_ASSERT(ac.degree() == 0, ac.degree());
    PO_ASSERT(equal(ac.degrees(), {}), ac.degrees());
  }

  {
    const po::polynomial ac = instantiate(integral(po::D(14., 5), {2, {1, 3}}));

    PO_ASSERT(unordered_equal_terms(
      ac,
      {
        {0, {}}
      }),
      ac);

    PO_ASSERT(ac.rank() == 0, ac.rank());
    PO_ASSERT(ac.degree() == 0, ac.degree());
    PO_ASSERT(equal(ac.degrees(), {}), ac.degrees());
  }

  {
    const po::polynomial ac = instantiate(integral(po::D(po::expr_constant{-0.004}, 5), {2, {1, 3}}));

    PO_ASSERT(unordered_equal_terms(
      ac,
      {
        {0, {}}
      }),
      ac);

    PO_ASSERT(ac.rank() == 0, ac.rank());
    PO_ASSERT(ac.degree() == 0, ac.degree());
    PO_ASSERT(equal(ac.degrees(), {}), ac.degrees());
  }
#if 0
  // TODO
  {
    const auto x = po::D(-3.7, 1);

    const po::polynomial ac = instantiate(integral(x, {2, {1, 3}}), po::rank<3>{});

    PO_ASSERT(unordered_equal_terms(
      ac,
      {
        {0, {0, 0, 0}}
      }),
      ac);

    PO_ASSERT(ac.rank() == 3, ac.rank());
    PO_ASSERT(ac.degree() == 0, ac.degree());
    PO_ASSERT(equal(ac.degrees(), {0, 0, 0}), ac.degrees());
  }
#endif

  PO_LINE;
}
