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

    assert(r.rank() == 1);
    assert(r.degree() == 3);
    assert(compare::equal(r.degrees(), {3}));

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

    assert(r.rank() == 3);
    assert(r.degree() == 5);
    assert(compare::equal(r.degrees(), {3, 4, 1}));

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

    assert(r.rank() == 3);
    assert(r.degree() == 5);
    assert(compare::equal(r.degrees(), {3, 4, 1}));

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

  // Construction count
  {
    po::polynomial p{{6, {0, 4, 1}}, {-2.3, {3, 1, 1}}};
    po::polynomial q{{6, {3, 1, 1}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial r = po::instantiate(q - p, po::rank<3>{});

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 1, count_diff);

    PO_LINE;
  }

  // Construction count
  {
    po::polynomial p{{6, {0, 4, 1}}, {-2.3, {3, 1, 1}}};
    po::polynomial q{{6, {3, 1, 1}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::instantiate(q - p, po::rank<3>{});

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 1, count_diff);

    PO_LINE;
  }
}

