#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_add_eq_binary_expr_level_2()
{
  // special case, branch test
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};

    p += p + p;

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

  // special case, branch test
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{2, {1, 1, 1, 1}}};
    po::polynomial r{{2, {1, 1, 1, 1}}};

    p += q + r;

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

  // special case, branch test
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{2, {1, 1, 1, 1}}};

    p += p + q;

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

  // special case, branch test
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    po::polynomial q{{2, {1, 1, 1, 1}}};
    p += q + p;

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

  // RS rvalue
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};

    p += 2 + 6*po::polynomial{{3, {2, 1, 4, 2}}};

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 2, {0, 0, 0, 0}},
        { 2, {1, 1, 1, 1}},
        {18, {2, 1, 4, 2}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {2, 1, 4, 2}), p.degrees());

    PO_LINE;
  }

  // LS copy is operand in RS
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    auto r = p;

    p += 2 + 6*r;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 2, {0, 0, 0, 0}},
        {14, {1, 1, 1, 1}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 4, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {1, 1, 1, 1}), p.degrees());

    PO_LINE;
  }

  // LS copy is operand in RS, test 2
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};
    auto r = p;

    p += q - 8.2*r;

    PO_ASSERT(compare::unordered_near_rel_terms(
      p,
      {
        {-14.4, {1, 1, 1, 1}},
        {-21.6, {0, 4, 2, 0}},
        {    3, {2, 1, 4, 2}},
        {    1, {1, 0, 0, 0}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {2, 4, 4, 2}), p.degrees());

    PO_LINE;
  }

  // LS is an operand in RS, test 1
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};

    p += 2 + 5*p;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 2, {0, 0, 0, 0}},
        {12, {1, 1, 1, 1}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 4, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {1, 1, 1, 1}), p.degrees());

    PO_LINE;
  }

  // LS is an operand in RS, test 2
  {
    po::polynomial p{{2, {1, 1, 1, 1}}};
    auto& r = p;

    p += 2 + 5*r;

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 2, {0, 0, 0, 0}},
        {12, {1, 1, 1, 1}},
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 4, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {1, 1, 1, 1}), p.degrees());

    PO_LINE;
  }

  // LS is an operand in RS, test 3
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};
    auto& r = p;

    p += q - 8.2*r;

    PO_ASSERT(compare::unordered_near_rel_terms(
      p,
      {
        {-14.4, {1, 1, 1, 1}},
        {-21.6, {0, 4, 2, 0}},
        {    3, {2, 1, 4, 2}},
        {    1, {1, 0, 0, 0}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {2, 4, 4, 2}), p.degrees());

    PO_LINE;
  }

  // LS is an operand in RS, test 3
  {
    po::polynomial p{{2, {1, 1, 1, 1}}, {3, {0, 4, 2, 0}}};
    po::polynomial q{{3, {2, 1, 4, 2}}, {1, {1, 0, 0, 0}}};

    p += q - 8.2*p;

    PO_ASSERT(compare::unordered_near_rel_terms(
      p,
      {
        {-14.4, {1, 1, 1, 1}},
        {-21.6, {0, 4, 2, 0}},
        {    3, {2, 1, 4, 2}},
        {    1, {1, 0, 0, 0}}
      }),
      p);

    PO_ASSERT(p.rank() == 4, p.rank());
    PO_ASSERT(p.degree() == 9, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {2, 4, 4, 2}), p.degrees());

    PO_LINE;
  }
}