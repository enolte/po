#include "../../polynomial.h"

#include "compare.h"

#include <cassert>

void test_ctor_terms_initialization()
{
  {
    po::polynomial p{0, po::rank<0>{}};
    assert(compare::equal(p.terms.cbegin()->exponents, {}));
  }

  {
    po::polynomial p{7.5, po::rank<0>{}};
    assert(compare::equal(p.terms.cbegin()->exponents, {}));
  }

  {
    po::polynomial p{7.5, po::rank<6>{}};
    assert(compare::equal(p.terms.cbegin()->exponents, 0, 0, 0, 0, 0, 0));
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}};

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(compare::equal(actual, expected));
  }
/*
  // Disabled for operator overload resolution
  {
    po::polynomial p{1.4, {2, 3, 2, 1}};

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(compare::equal(actual, expected));
  }

  {
    po::polynomial p({1.4, {2, 3, 2, 1}});

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(compare::equal(actual, expected));
  }

  {
    po::polynomial p(1.4, {2, 3, 2, 1});

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(compare::equal(actual, expected));
  }
*/
  {
    po::polynomial p({{1.4, {2, 3, 2, 1}}});

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(compare::equal(actual, expected));
  }

  {
    po::polynomial p(1.4, 2, 3, 2, 1);

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(compare::equal(actual, expected));
  }

  {
    po::polynomial p{1.4, 2, 3, 2, 1};

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(compare::equal(actual, expected));
  }

  {
    po::polynomial p({{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}});

    PO_ASSERT(
      unordered_equal(
        p.terms,
        {
          { 2.4, {3, 2, 3, 2}},
          {-0.6, {1, 1, 1, 1}}
        }),
      p);
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};

    PO_ASSERT(
      unordered_equal(
        p.terms,
        {
          {2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}
        }),
      p);
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
    po::polynomial copied{p};

    assert(unordered_equal(p.terms, copied.terms));
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
    po::polynomial moved{std::move(p)};

    PO_ASSERT(
      unordered_equal(
        moved.terms,
        {
          {-0.6, {1, 1, 1, 1}},
          { 2.4, {3, 2, 3, 2}}
        }),
        moved);

    assert(p.nterms() == 0);
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}, {47.2, {0, 0, 0, 0}}};
    po::polynomial moved{std::move(p)};

    assert(unordered_equal(
      moved.terms,
      {
        { 2.4, {3, 2, 3, 2}},
        {47.2, {0, 0, 0, 0}},
        {-0.6, {1, 1, 1, 1}},
      }));

    assert(p.nterms() == 0);
  }

  PO_LINE;
}
