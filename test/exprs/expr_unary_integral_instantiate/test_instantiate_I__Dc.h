#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_I__Dc()
{
  {
    const auto x = po::D(-3.7, 1);

    const po::polynomial ac = instantiate(integral(x, {2, {1, 3}}));

    PO_ASSERT(compare::unordered_equal_terms(
      ac,
      {
        {0, {}}
      }),
      ac);

    PO_ASSERT(ac.rank() == 0, ac.rank());
    PO_ASSERT(ac.degree() == 0, ac.degree());
    PO_ASSERT(compare::equal(ac.degrees(), {}), ac.degrees());

    PO_LINE;
  }

  {
    const po::polynomial ac = instantiate(integral(po::D(14., 5), {2, {1, 3}}));

    PO_ASSERT(compare::unordered_equal_terms(
      ac,
      {
        {0, {}}
      }),
      ac);

    PO_ASSERT(ac.rank() == 0, ac.rank());
    PO_ASSERT(ac.degree() == 0, ac.degree());
    PO_ASSERT(compare::equal(ac.degrees(), {}), ac.degrees());

    PO_LINE;
  }

  {
    const po::polynomial ac = instantiate(integral(po::D(po::expr_constant{-0.004}, 5), {2, {1, 3}}));

    PO_ASSERT(compare::unordered_equal_terms(
      ac,
      {
        {0, {}}
      }),
      ac);

    PO_ASSERT(ac.rank() == 0, ac.rank());
    PO_ASSERT(ac.degree() == 0, ac.degree());
    PO_ASSERT(compare::equal(ac.degrees(), {}), ac.degrees());

    PO_LINE;
  }
#if 0
  // TODO
  {
    const auto x = po::D(-3.7, 1);

    const po::polynomial ac = instantiate(integral(x, {2, {1, 3}}), po::rank<3>{});

    PO_ASSERT(compare::unordered_equal_terms(
      ac,
      {
        {0, {0, 0, 0}}
      }),
      ac);

    PO_ASSERT(ac.rank() == 3, ac.rank());
    PO_ASSERT(ac.degree() == 0, ac.degree());
    PO_ASSERT(compare::equal(ac.degrees(), {0, 0, 0}), ac.degrees());

    PO_LINE;
  }
#endif
}
