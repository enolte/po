#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_p__plus__c()
{
  // Through op=(polynomial)
  {
    po::polynomial p{{6, {0}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial r = po::instantiate(p + -4, po::rank<1>{});

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 1, count_diff);

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {2, {0}}
      }),
      r);

    PO_LINE;
  }

  // Same as above, through op=(Expr)
  {
    po::polynomial p{{6, {0}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial r = p + -4;

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    // TODO Should be 1
    PO_ASSERT(count_diff == 2, count_diff);

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
    po::polynomial r = po::instantiate(p + -4, po::rank<2>{});

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
    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial{{6, {0, 2}}, {3, {1, 1}}} + -4;

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 1, count_diff);

    PO_LINE;
  }
}


