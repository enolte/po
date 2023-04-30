#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_ctor_terms_initialization()
{
  {
    po::polynomial p{po::polynomial::make_zero(po::rank<0>{})};
    assert(p.nterms() == 0);

    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_constant(po::rank<0>{}, 7.5)};
    assert(p.nterms() == 1);
    assert(compare::equal(p.terms.cbegin()->exponents, {}));

    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_constant(po::rank<6>{}, 7.5)};
    assert(p.nterms() == 1);
    assert(compare::equal(p.terms.cbegin()->exponents, {0, 0, 0, 0, 0, 0}));

    PO_LINE;
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}};

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(p.nterms() == 1);
    assert(compare::equal(actual, expected));

    PO_LINE;
  }

  {
    po::polynomial p({{1.4, {2, 3, 2, 1}}});

    const po::exponents expected{2, 3, 2, 1};
    const po::exponents actual{p.terms[0].exponents};

    assert(p.nterms() == 1);
    assert(compare::equal(actual, expected));

    PO_LINE;
  }

  {
    po::polynomial p({{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}});

    PO_ASSERT(
      compare::unordered_equal_terms(
        p,
        {
          { 2.4, {3, 2, 3, 2}},
          {-0.6, {1, 1, 1, 1}}
        }),
      p);

    assert(p.nterms() == 2);

    PO_LINE;
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};

    PO_ASSERT(
      compare::unordered_equal_terms(
        p,
        {
          {2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}
        }),
      p);

    assert(p.nterms() == 2);

    PO_LINE;
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
    po::polynomial copied{p};

    assert(compare::unordered_equal_terms(p, copied));

    assert(p.nterms() == 2);

    PO_LINE;
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
    po::polynomial moved{std::move(p)};

    PO_ASSERT(
      compare::unordered_equal_terms(
        moved,
        {
          {-0.6, {1, 1, 1, 1}},
          { 2.4, {3, 2, 3, 2}}
        }),
        moved);

    assert(p.nterms() == 0);

    PO_LINE;
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}, {47.2, {0, 0, 0, 0}}};
    po::polynomial moved{std::move(p)};

    assert(compare::unordered_equal_terms(
      moved,
      {
        { 2.4, {3, 2, 3, 2}},
        {47.2, {0, 0, 0, 0}},
        {-0.6, {1, 1, 1, 1}},
      }));

    assert(p.nterms() == 0);

    PO_LINE;
  }
}
