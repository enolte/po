#include "../../../polynomial.h"
#include "../../macros.h"
#include <cassert>

void test_instantiate_p()
{
  {
    po::polynomial p{{6, {0}}};

    po::polynomial r = po::instantiate(p, po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {6, {0}},
      }),
      r);

    assert(r.rank() == 1);
    assert(r.degree() == 0);
    assert((compare::equal(r.degrees(), p.degrees())));
    assert((compare::equal(r.degrees(), po::exponents{0})));

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    assert(expr_rank(p) == p.rank());

    po::polynomial r = po::instantiate(p, po::rank<3>{});

    assert(compare::unordered_equal_terms(
      r,
      {
        { 6  , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}}
      }));

    assert(r.rank() == 3);
    assert(r.degree() == 16);
    assert((compare::equal(r.degrees(), p.degrees())));
    assert((compare::equal(r.degrees(), po::exponents{10, 5, 3})));

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    po::polynomial r = po::instantiate(p);
    assert(compare::unordered_equal_terms(
      r,
      {
        { 6  , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}}
      }));

    assert(r.rank() == 3);
    assert(r.degree() == 16);
    assert((compare::equal(r.degrees(), p.degrees())));
    assert((compare::equal(r.degrees(), po::exponents{10, 5, 3})));

    PO_LINE;
  }

}
