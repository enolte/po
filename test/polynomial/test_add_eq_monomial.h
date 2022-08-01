#include "../../polynomial.h"

using po::operator<<;

#include <cassert>

void test_add_eq_monomial()
{
  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 4);
    assert(p.coefficient(1, 0, 0) == 2.5);
    assert(compare::equal(p.variable_degrees, 3, 1, 0));

    p += {2.5, {1, 0, 0}};

    assert(p.nterms() == 4);
    assert(p.coefficient(1, 0, 0) == 5);
    assert(compare::equal(p.variable_degrees, 3, 1, 0));

    p += {2.5, {1, 7, 0}};

    assert(p.nterms() == 5);
    assert(p.coefficient(1, 7, 0) == 2.5);
    assert(compare::equal(p.variable_degrees, 3, 7, 0));
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 1, 0}},
      {-3 , {0, 0, 0}},
      {2.5, {1, 0, 0}}
    });

    assert(p.nterms() == 4);
    assert(p.coefficient(1, 0, 0) == 2.5);
    assert(compare::equal(p.variable_degrees, 3, 1, 0));

    p += {2.5, {1, 0, 0}};

    assert(p.nterms() == 4);
    assert(p.coefficient(1, 0, 0) == 5);
    assert(compare::equal(p.variable_degrees, 3, 1, 0));

    p += {2.5, {1, 7, 0}};

    assert(p.nterms() == 5);
    assert(p.coefficient(1, 7, 0) == 2.5);
    assert(compare::equal(p.variable_degrees, 3, 7, 0));
  }

  {
    po::polynomial p
    ({
      { 1., {3, 0, 0}},
      {-4 , {1, 5, 0}},
      {-3 , {0, 0, 0}},
      {5.0, {1, 0, 0}}
    });

    assert(p.nterms() == 4);
    assert(p.coefficient(1, 0, 0) == 5);
    assert(compare::equal(p.variable_degrees, 3, 5, 0));

    p += {1.7, {0, 3, 2}};

    assert(p.nterms() == 5);
    PO_ASSERT(compare::equal(p.variable_degrees, 3, 5, 2), p.variable_degrees);

    PO_ASSERT((unordered_equal(
      p.terms,
      {
        { 1., {3, 0, 0}},
        {-4 , {1, 5, 0}},
        {-3 , {0, 0, 0}},
        {5.0, {1, 0, 0}},
        {1.7, {0, 3, 2}},
      })),
      p);
  }

  {
    po::polynomial p
    {{-3.6, {1, 1, 4, 3, 0, 0, 4}},
     {-1.9, {8, 2, 0, 4, 0, 3, 3}},
     {12.5, {0, 5, 4, 0, 0, 1, 0}}};

    assert(p.nterms() == 3);
    assert(compare::equal(p.variable_degrees, 8, 5, 4, 4, 0, 3, 4));

    const auto nterms_at_entry = p.nterms();

    p += {3.22, {0, 0, 0, 0, 0, 0, 4}};

    assert(p.nterms() == nterms_at_entry + 1);
    assert(compare::equal(p.variable_degrees, 8, 5, 4, 4, 0, 3, 4));

    p.add(3.22, 4, 0, 0, 0, 0, 0, 4);
    assert(p.nterms() == nterms_at_entry + 2);
    assert(compare::equal(p.variable_degrees, 8, 5, 4, 4, 0, 3, 4));

    p.add(3.22, 4, 0, 0, 0, 0, 0, 4);
    assert(p.nterms() == nterms_at_entry + 2);
    assert(compare::equal(p.variable_degrees, 8, 5, 4, 4, 0, 3, 4));

    p.add(75.05, {0, 1, 1, 0, 0, 4, 0});
    assert(p.nterms() == nterms_at_entry + 3);
    assert(compare::equal(p.variable_degrees, 8, 5, 4, 4, 0, 4, 4));

    p.add(75.05, 0, 1, 1, 0, 0, 4, 0);
    assert(p.nterms() == nterms_at_entry + 3);
    assert(compare::equal(p.variable_degrees, 8, 5, 4, 4, 0, 4, 4));

    po::monomial m{-5.6, {0, 0, 0, 3, 0, 0, 0}};

    p += m;
    assert(p.nterms() == nterms_at_entry + 4);
    assert(compare::equal(p.variable_degrees, 8, 5, 4, 4, 0, 4, 4));

    p -= m;
    // A term with a zero coefficient is preserved.
    assert(p.nterms() == nterms_at_entry + 4);
    assert(compare::equal(p.variable_degrees, 8, 5, 4, 4, 0, 4, 4));
  }

  {
    po::polynomial k{po::rank<7>{}};
    for(std::size_t i = 0; i < 4; ++i)
      k += {double(3*i + 1), {i, i, i, 2*i, 0, 0, i}};

    assert(k.nterms() == 4);
    PO_ASSERT(unordered_equal(k.terms,
      {
        { 1, {0, 0, 0, 0, 0, 0, 0}},
        { 4, {1, 1, 1, 2, 0, 0, 1}},
        { 7, {2, 2, 2, 4, 0, 0, 2}},
        {10, {3, 3, 3, 6, 0, 0, 3}},
      }
    ),
    k);
  }

  PO_LINE;
}

