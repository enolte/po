#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_c__plus__p()
{

  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(-4 + p, po::rank<1>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {2, {0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};

    po::polynomial r = po::instantiate(-4 + p, po::rank<2>{});

    assert(compare::unordered_equal_terms(
      r,
      {
        { 6, {0, 2}},
        { 3, {1, 1}},
        {-4, {0, 0}}
      }));

    PO_LINE;
  }

  // Construction count
  {
    po::polynomial q{{6, {0, 2}}, {3, {1, 1}}};

    po::polynomial p = po::zero(q.rank());

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::instantiate(p, -4 + q, q.rank());

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 0, count_diff);

    PO_LINE;
  }

  // Construction count
  {
    po::polynomial q{{6, {0, 2}}, {3, {1, 1}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::instantiate(-4 + q);

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 1, count_diff);

    PO_LINE;
  }

  // TODO
/*
  // Construction count
  {
    po::polynomial q{{6, {0, 2}}, {3, {1, 1}}};

    po::polynomial p = po::zero(q.rank());

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::instantiate(p, -4 + q);

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 2, count_diff);

    PO_LINE;
  }

  // Construction count
  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::instantiate(p, -4 + p, p.rank());

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 1, count_diff);

    PO_LINE;
  }
*/
}
