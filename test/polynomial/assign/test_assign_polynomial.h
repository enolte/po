#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_assign_polynomial()
{
  // Assign lvalue polynomial
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    po::polynomial q = po::polynomial::make_constant(po::rank<6>{}, 3.1);

    q = p;

    assert(compare::unordered_equal_terms(
      q,
      {
        {4.2, {4, 0, 7, 6, 5}},
        {5.5, {3, 1, 1, 0, 0}}
      }));

    PO_ASSERT(q == p, p);
    assert(q.rank() == 5);
    assert(q.degree() == 22);
    assert(compare::equal(q.degrees(), {4, 1, 7, 6, 5}));

    PO_LINE;
  }

  // Assign rvalue polynomial
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    po::polynomial q = po::polynomial::make_constant(po::rank<6>{}, 3.1);

    const std::uint64_t count_before = po::polynomial::construction_count();

    q = std::move(p);

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 0, count_diff);

    assert(compare::unordered_equal_terms(
      q,
      {
        {4.2, {4, 0, 7, 6, 5}},
        {5.5, {3, 1, 1, 0, 0}}
      }));

    PO_ASSERT(p.terms.size() == 0, p);
    assert(q.rank() == 5);
    assert(q.degree() == 22);
    assert(compare::equal(q.degrees(), {4, 1, 7, 6, 5}));

    PO_LINE;
  }

  // Assign prvalue polynomial
  {
    po::polynomial q = po::polynomial::make_constant(po::rank<6>{}, 3.1);

    const std::uint64_t count_before = po::polynomial::construction_count();

    q = {{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 0, count_diff);

    assert(compare::unordered_equal_terms(
      q,
      {
        {4.2, {4, 0, 7, 6, 5}},
        {5.5, {3, 1, 1, 0, 0}}
      }));

    assert(q.rank() == 5);
    assert(q.degree() == 22);
    PO_ASSERT(compare::equal(q.degrees(), {4, 1, 7, 6, 5}), q.degrees());

    PO_LINE;
  }
}
