#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_add_eq_binary_expr_level_1()
{
  {
    po::polynomial p{{6, {0}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    p += 7 + p;

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 0, count_diff);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {19, {0}},
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    p += p + 7;

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 0, count_diff);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {19, {0}},
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0}}};
    po::polynomial q{{6, {3}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    p += -q;

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    // TODO want 0 here
    PO_ASSERT(count_diff == 1, count_diff);


    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 6, {0}},
        {-6, {3}},
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0}}};
    po::polynomial q{{6, {3}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    p += q - q;

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 0, count_diff);


    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {6, {0}},
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0}}};
    po::polynomial q{{6, {3}}};

    p += p - q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {12, {0}},
        {-6, {3}}
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0}}};
    po::polynomial q{{6, {3}}};

    p += q - p;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {6, {3}},
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{6, {0}}};

    p += p - p;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {6, {0}}
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    p += 2*p;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 6, {1, 1, 1, 1}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 4, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {1, 1, 1, 1}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};
    p += +q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 2, {1, 1, 1, 1}},
        { 3, {2, 1, 4, 2}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {2, 1, 4, 2}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    p += 2 + p;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 4, {1, 1, 1, 1}},
        { 2, {0, 0, 0, 0}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 4, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {1, 1, 1, 1}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};
    p += 2 + q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 2, {1, 1, 1, 1}},
        { 3, {2, 1, 4, 2}},
        { 2, {0, 0, 0, 0}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {2, 1, 4, 2}), p.degrees());

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p += std::move(6 - q);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 2, {1, 1, 1, 1}},
        { 6, {0, 0, 0, 0}},
        {-3, {2, 1, 4, 2}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {2, 1, 4, 2}), p.degrees());

    // TODO A move has no effect on a polynomial in a += expression
    PO_ASSERT(compare::unordered_equal_terms(
      q,
      {
        {3, {2, 1, 4, 2}}
      }),
      q);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}};

    p += q*q;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {2, {1, 1, 1, 1}},
        {3, {0, 4, 2, 0}},
        {9, {4, 2, 8, 4}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 18, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {4, 4, 8, 4}), p.degrees());

    PO_LINE;
  }
}
