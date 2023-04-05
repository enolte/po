#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p__minus__p()
{
  {
    po::polynomial p{{6, {0}}};
    po::polynomial q{{6, {3}}};

    po::polynomial r = po::instantiate(p - q, po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {6, {0}},
        {-6, {3}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 4, 1}}};
    po::polynomial q{{6, {3, 1, 1}}};

    po::polynomial r = po::instantiate(p - q, po::rank<3>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {6, {0, 4, 1}},
        {-6, {3, 1, 1}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 4, 1}}, {-2.3, {3, 1, 1}}};
    po::polynomial q{{6, {3, 1, 1}}};

    po::polynomial r = po::instantiate(p - q, po::rank<3>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        { 6  , {0, 4, 1}},
        {-8.3, {3, 1, 1}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 4, 1}}, {-2.3, {3, 1, 1}}};
    po::polynomial q{{6, {3, 1, 1}}};

    po::polynomial r = po::instantiate(q - p, po::rank<3>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {-6  , {0, 4, 1}},
        { 8.3, {3, 1, 1}}
      }),
      r);

    assert(r.rank() == 3);
    assert(r.degree() == 5);
    assert(compare::equal(r.degrees(), {3, 4, 1}));

    PO_LINE;
  }

}

