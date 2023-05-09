#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_add_eq_scalar()
{
  // Add field scalar to polynomial with empty storage (zero terms)
  {
    po::polynomial p = po::polynomial::make_zero(po::rank<5>{});

    assert(p.nterms() == 0);
    assert(p.constant() == 0);
    assert(p.coefficient(0, 0, 0, 0, 0) == 0.);

    p += 8.;

    assert(compare::unordered_equal_terms(
      p,
      {
        {8., {0, 0, 0, 0, 0}}
      }));

    assert(p.nterms() == 1);
    assert(p.constant() == 8.);
    assert(p.coefficient(0, 0, 0, 0, 0) == 8.);

    PO_LINE;
  }

  // Add field scalar to polynomial with non-empty storage, no matching multiindex
  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 3);
    assert(p.constant() == 0);
    assert(p.coefficient(0, 0, 0) == 0.);

    p += 8.;

    assert(p.nterms() == 4);
    assert(p.constant() == 8);
    assert(p.coefficient(0, 0, 0) == 8.);

    PO_LINE;
  }

  // Add field scalar to polynomial with non-empty storage, matching multiindex
  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 4);
    assert(p.constant() == -3.);
    assert(p.coefficient(0, 0, 0) == -3.);

    p += 8.;

    assert(compare::unordered_equal_terms(
      p,
      {
        { 1., {3, 0, 0}},
        {-4 , {1, 1, 0}},
        { 5 , {0, 0, 0}},
        {2.5, {1, 0, 0}}
      }));

    assert(p.nterms() == 4);
    assert(p.constant() == 5.);
    assert(p.coefficient(0, 0, 0) == 5.);

    PO_LINE;
  }

  // Add non-field scalar to polynomial with non-empty storage, no matching multiindex
  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 4);
    assert(p.constant() == -3.);
    assert(p.coefficient(0, 0, 0) == -3.);

    p += {8.};

    assert(p.nterms() == 4);
    assert(p.constant() == 5.);
    assert(p.coefficient(0, 0, 0) == 5.);

    PO_LINE;
  }

  // Add non-field scalar to polynomial with non-empty storage, no matching multiindex
  {
    po::polynomial p{{-7.1, {4, 1, 2, 2, 5}}, {4.9, {5, 0, 0, 0, 5}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    p += 8.f;

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 0, count_diff);

    PO_ASSERT(p.nterms() == 3, p);
    assert(p.constant() == 8.);
    PO_ASSERT(p.coefficient(0, 0, 0, 0, 0) == 8., p);

    PO_LINE;
  }

  // Add non-field scalar to polynomial with non-empty storage, no matching multiindex
  {
    po::polynomial p{{-7.1, {4, 1, 2, 2, 5}}, {4.9, {5, 0, 0, 0, 5}}};

    const std::uint64_t count_before = po::polynomial::construction_count();

    p += 8u;

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 0, count_diff);

    PO_ASSERT(p.nterms() == 3, p);
    assert(p.constant() == 8.);
    PO_ASSERT(p.coefficient(0, 0, 0, 0, 0) == 8., p);

    PO_LINE;
  }
}


