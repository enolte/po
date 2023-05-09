#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_p__plus__p_mult_p()
{
  // x0 + x1
  {
    po::polynomial q{{3, {0, 5, 3}}};
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};
    po::polynomial s{{3, {0, 1, 1}}, {2, {1, 0, 2}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial z = po::instantiate(s + q*r, po::rank<3>{});

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    // TODO Should be 1
    PO_ASSERT(count_diff == 2, count_diff);

    PO_ASSERT(compare::unordered_near_rel_terms(
      z,
      {
        {9, {1, 6, 4}}, {6, {1, 6, 5}}, {3, {0, 1, 1}}, {2, {1, 0, 2}}
      }),
      z);

    PO_LINE;
  }

  // Construction count
  {
    po::polynomial q{{3, {0, 5, 3}}};
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};
    po::polynomial s{{3, {0, 1, 1}}, {2, {1, 0, 2}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial z = po::instantiate(s + q*r);

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    // TODO Should be 1
    PO_ASSERT(count_diff == 2, count_diff);

    PO_ASSERT(compare::unordered_near_rel_terms(
      z,
      {
        {9, {1, 6, 4}}, {6, {1, 6, 5}}, {3, {0, 1, 1}}, {2, {1, 0, 2}}
      }),
      z);

    PO_LINE;
  }

  // Construction count
  {
    po::polynomial q{{3, {0, 5, 3}}};
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};
    po::polynomial s{{3, {0, 1, 1}}, {2, {1, 0, 2}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial z = s + q*r;

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    // TODO Should be 1
    PO_ASSERT(count_diff == 3, count_diff);

    PO_ASSERT(compare::unordered_near_rel_terms(
      z,
      {
        {9, {1, 6, 4}}, {6, {1, 6, 5}}, {3, {0, 1, 1}}, {2, {1, 0, 2}}
      }),
      z);

    PO_LINE;
  }

  // Construction count
  {
    po::polynomial q{{3, {0, 5, 3}}};
    po::polynomial r{{3, {1, 1, 1}}, {2, {1, 1, 2}}};
    po::polynomial s{{3, {0, 1, 1}}, {2, {1, 0, 2}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    s + q*r;

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 0, count_diff);

    PO_LINE;
  }
}