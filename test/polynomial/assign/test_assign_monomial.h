#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_assign_monomial_lvalue();
void test_assign_monomial_rvalue();
void test_assign_monomial_prvalue();

void test_assign_monomial()
{
  test_assign_monomial_lvalue();
  test_assign_monomial_rvalue();
  test_assign_monomial_prvalue();
}

void test_assign_monomial_lvalue()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    po::monomial m(3.1, {2, 5, 2});

    p = m;

    assert(compare::unordered_equal_terms(
      p,
      {
        {3.1, {2, 5, 2}}
      }));

    assert(p.rank() == 3);
    assert(p.degree() == 9);
    PO_ASSERT(compare::equal(p.degrees(), {2, 5, 2}), p.degrees());

    PO_LINE;
  }
}

void test_assign_monomial_rvalue()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    po::monomial m(3.1, {2, 5, 2});

    p = std::move(m);

    assert(compare::unordered_equal_terms(
      p,
      {
        {3.1, {2, 5, 2}}
      }));

    assert(p.rank() == 3);
    assert(p.degree() == 9);
    PO_ASSERT(compare::equal(p.degrees(), {2, 5, 2}), p.degrees());

    PO_LINE;
  }
}

void test_assign_monomial_prvalue()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    p = {3.1, {2, 5, 2}};

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 0, count_diff);

    assert(compare::unordered_equal_terms(
      p,
      {
        {3.1, {2, 5, 2}}
      }));

    assert(p.rank() == 3);
    assert(p.degree() == 9);
    PO_ASSERT(compare::equal(p.degrees(), {2, 5, 2}), p.degrees());

    PO_LINE;
  }
}