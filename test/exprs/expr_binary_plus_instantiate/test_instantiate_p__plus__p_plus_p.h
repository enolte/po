#include "../../../polynomial.h"
#include <cassert>

void test_instantiate_p__plus__p_plus_p()
{
  // x0 + x1
  {
    po::polynomial p{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{ 3, {0, 5, 3}}};
    po::polynomial r{{-6, {0, 5, 3}}, { 5.6, {3, 3, 1}}, {5.1, { 7, 5, 1}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial s = po::instantiate(p + (q + r), po::rank<3>{});

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 2, count_diff);

    assert(compare::unordered_near_rel_terms(
      s,
      {
        { 3. , { 0, 5, 3}},
        { 3.2, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        { 5.1, { 7, 5, 1}}
      }));

    PO_LINE;
  }

  // Construction count
  {
    po::polynomial p{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{ 3, {0, 5, 3}}};
    po::polynomial r{{-6, {0, 5, 3}}, { 5.6, {3, 3, 1}}, {5.1, { 7, 5, 1}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial s = po::instantiate(p + (q + r));

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    // TODO Should be 1
    PO_ASSERT(count_diff == 2, count_diff);

    assert(compare::unordered_near_rel_terms(
      s,
      {
        { 3. , { 0, 5, 3}},
        { 3.2, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        { 5.1, { 7, 5, 1}}
      }));

    PO_LINE;
  }

  // Construction count
  {
    po::polynomial p{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};
    po::polynomial q{{ 3, {0, 5, 3}}};
    po::polynomial r{{-6, {0, 5, 3}}, { 5.6, {3, 3, 1}}, {5.1, { 7, 5, 1}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial s = p + (q + r);

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    // TODO Should be 2
    PO_ASSERT(count_diff == 3, count_diff);

    assert(compare::unordered_near_rel_terms(
      s,
      {
        { 3. , { 0, 5, 3}},
        { 3.2, { 3, 3, 1}},
        { 5.1, {10, 5, 1}},
        { 5.1, { 7, 5, 1}}
      }));

    PO_LINE;
  }

  // Construction count
  {
    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}} +
    po::polynomial{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}} +
    po::polynomial{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    // TODO This should be 3
    PO_ASSERT(count_diff == 7, count_diff);

    PO_LINE;
  }

  // Construction count
  {
    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial{{ 6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}} +
    po::polynomial{{ 3, {0, 5, 3}}} +
    po::polynomial{{-6, {0, 5, 3}}, { 5.6, {3, 3, 1}}, {5.1, { 7, 5, 1}}};

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    // TODO This should be 3
    PO_ASSERT(count_diff == 7, count_diff);

    PO_LINE;
  }


}
