#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>


void test_instantiate_pos__pos_pos_pos_pos_pos_p()
{
  {
    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial p{{6, {0, 5, 3}}, {-2.4, {3, 3, 1}}, {5.1, {10, 5, 1}}};

    po::polynomial r = po::instantiate(+ + + + + +p, po::rank<3>{});

    assert(compare::unordered_equal_terms(
      r,
      {
        { 6  , { 0, 5, 3}},
        {-2.4, { 3, 3, 1}},
        { 5.1, {10, 5, 1}}
      }));

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 2, count_diff);

    PO_LINE;
  }

}
