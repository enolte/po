#include "../../polynomial.h"

#include "compare.h"

#include <cassert>

void test_ctor_terms_initialization()
{
  {
    po::polynomial p{po::rank<0>{}};
    assert(p.nterms() == 0);
  }

  {
    po::polynomial p{0, po::rank<0>{}};
    assert(p.nterms() == 1 && equal(p.terms.cbegin()->exponents, {}));
  }

  {
    po::polynomial p{7.5, po::rank<0>{}};
    assert(p.nterms() == 1 && equal(p.terms.cbegin()->exponents, {}));
  }

  {
    po::polynomial p{7.5, po::rank<6>{}};
    assert(p.nterms() == 1 && equal(p.terms.cbegin()->exponents, 0, 0, 0, 0, 0, 0));
  }

  {
    using namespace po;
    polynomial p(rank<15>{});
    assert(p.nterms() == 0);
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}};

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(p.nterms() == 1 && equal(actual, expected));
  }
/*
  // Disabled for operator overload resolution
  {
    po::polynomial p{1.4, {2, 3, 2, 1}};

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(p.nterms() == 1 && equal(actual, expected));
  }

  {
    po::polynomial p({1.4, {2, 3, 2, 1}});

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(p.nterms() == 1 && equal(actual, expected));
  }

  {
    po::polynomial p(1.4, {2, 3, 2, 1});

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(p.nterms() == 1 && equal(actual, expected));
  }
*/
  {
    po::polynomial p({{1.4, {2, 3, 2, 1}}});

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(p.nterms() == 1 && equal(actual, expected));
  }

  {
    po::polynomial p(1.4, 2, 3, 2, 1);

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(p.nterms() == 1 && equal(actual, expected));
  }

  {
    po::polynomial p{1.4, 2, 3, 2, 1};

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(p.nterms() == 1 && equal(actual, expected));
  }

  {
    po::polynomial p({{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}});

    PO_ASSERT(
      p.nterms() == 2 &&
      contains_unique(p.terms, {3, 2, 3, 2}) &&
      contains_unique(p.terms, {1, 1, 1, 1}),
      p);
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};

    PO_ASSERT(
      p.nterms() == 2 &&
      contains_unique(p.terms, {3, 2, 3, 2}) &&
      contains_unique(p.terms, {1, 1, 1, 1}),
      p);
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
    po::polynomial copied{p};

    assert(equal_exponents(p.terms, copied.terms));
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
    po::polynomial moved{std::move(p)};

    assert(
      moved.nterms() == 2 &&
      contains_unique(moved.terms, {3, 2, 3, 2}) &&
      contains_unique(moved.terms, {1, 1, 1, 1}));

    assert(p.nterms() == 0);
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}, {47.2, {0, 0, 0, 0}}};
    po::polynomial moved{std::move(p)};

    assert(equal_exponents(
      moved.terms,
      {{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}, {47.2, {0, 0, 0, 0}}}));

    assert(
      moved.nterms() == 3 &&
      contains_unique(moved.terms, {3, 2, 3, 2}) &&
      contains_unique(moved.terms, {1, 1, 1, 1}) &&
      contains_unique(moved.terms, {0, 0, 0, 0}));

    assert(p.nterms() == 0);
  }

  PO_LINE;
}
