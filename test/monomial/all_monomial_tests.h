#include <cassert>
#include <iostream>
#include <type_traits>
#include <algorithm>
#include <compare>

#include "../errors.h"
#include "../macros.h"

#include "../../types/monomial.h"

void evaluate();
void evaluate2();
void evaluate_incomplete();
void evaluate_partial();
void evaluate_partial_place_OOR();

void is_zero();
void is_constant();
void rank();
void degree();

namespace po_test
{
  void all_monomial_tests()
  {
    degree();
    rank();
    evaluate();
    evaluate2();
    evaluate_incomplete();
    evaluate_partial();
    evaluate_partial_place_OOR();
    is_zero();
    is_constant();

    std::vector<po::monomial> t;
    t.push_back({4.3, {3, 3, 4}});
    t.push_back({5.3, po::exponents{3, 3, 0}});
    t.emplace_back(2.3, po::exponents{3, 7, 4});
  }

}

void is_zero()
{
  po::monomial m{3.2, {5, 0, 1, 6}};
  assert(!m.is_zero());

  m.coefficient = 0.;
  assert(m.is_zero());

  m.coefficient = po::nan;
  assert(!m.is_zero());

  m = {};
  assert(m.is_zero());

  PO_LINE;
}

void is_constant()
{
  po::monomial m{3.2, {5, 0, 1, 6}};
  assert(!m.is_constant());

  m.coefficient = 0.;
  assert(!m.is_constant());

  m.coefficient = po::nan;
  assert(!m.is_constant());


  m.exponents = 0.;
  assert(m.is_constant());

  m.coefficient = 0.;
  assert(m.is_constant());

  m.coefficient = po::nan;
  assert(m.is_constant());


  m = {};
  m.coefficient = 7.3;
  assert(m.is_constant());

  m.coefficient = 0.;
  assert(m.is_constant());

  m.coefficient = po::nan;
  assert(m.is_constant());

  PO_LINE;
}

void degree()
{
  po::monomial m{3.2, {5, 0, 1, 6}};
  assert(m.degree() == 12);

  m = {};
  assert(m.degree() == 0);

  m = {0., {4, 3, 2, 1}};
  assert(m.degree() == 10);

  PO_LINE;
}

void rank()
{
  po::monomial m{3.2, {5, 0, 1, 6}};
  assert(m.rank() == 4);

  m = {};
  assert(m.rank() == 0);

  PO_LINE;
}

template<std::integral T>
using list = std::initializer_list<T>;

template<typename T>
constexpr int operator<=>(const po::exponents& x, std::initializer_list<T>&& y)
{
  if(std::ranges::equal(x, y))
    return 0;
  const auto mismatch{std::ranges::mismatch(x, y)};
  if(*mismatch.in1 < *mismatch.in2)
    return -1;
  else
    return 1;
}

template<typename T>
constexpr int operator<=>(const po::exponents& x, const po::exponents& y)
{
  if(std::ranges::equal(x, y))
    return 0;
  const auto mismatch{std::ranges::mismatch(x, y)};
  if(*mismatch.in1 < *mismatch.in2)
    return -1;
  else
    return 1;
}


void evaluate()
{
  // m(x, y, z, t) = 3.2 * x**5 * z * t**6
  const po::monomial m{3.2, {5, 0, 1, 6}};
  assert(0 == (m.exponents <=> list{5, 0, 1, 6}));

  // m(0, 0, ...) = 0 because there is a non-zero exponent
  {
    const double y = m(0, 0, 0, 0);
    assert(y == 0);
  }

  // m(1, 1, ...) = coefficient
  {
    const double y = m(1, 1, 1, 1);
    assert(y == m.coefficient);
  }

  // m(...) is invariant to 0-exponent components
  {
    const double y = m(1, 21.5, 1, 1);
    assert(y == 3.2);
  }

  // m(...) is invariant to 0-exponent components
  {
    const double y = m(1, -8.03, 1, 1);
    assert(y == 3.2);
  }

  // m(...) applies the constructed exponent to each argument
  {
    const double ex = 32 * m(1, 1, 1, 1);
    const double ac = m(2, 1, 1, 1);
    assert(ex == ac);
  }

  // m(...) applies the constructed exponent to each argument
  {
    const double ex = 729 * m(1, 1, 1, 1);
    const double ac = m(1, 1, 1, 3);
    assert(ex == ac);
  }

  PO_LINE;
}


void evaluate2()
{
  const po::monomial m{3.2, {5, 0, 1, 6, 5, 3, 5, 2, 10, 4, 2, 0, 5, 11, 3, 3, 7}};

  assert(std::ranges::equal(m.exponents, po::exponents{5, 0, 1, 6, 5, 3, 5, 2, 10, 4, 2, 0, 5, 11, 3, 3, 7}));

  // m(0, 0, ...) = 0 because there is a non-zero exponent
  {
    const double y = m(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    assert(y == 0);
  }

  // m(1, 1, ...) = coefficient
  {
    const double y = m(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    assert(y == m.coefficient);
  }

  // m(...) is invariant to 0-exponent components
  {
    const double y = m(1, 21.5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    assert(y == 3.2);
  }

  // m(...) is invariant to 0-exponent components
  {
    const double y = m(1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    assert(y == 3.2);
  }

  // m(...) applies the constructed exponent to each argument
  {
    const double ex = 32 * m(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    const double ac = m(2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    assert(ex == ac);
  }

  // m(...) applies the constructed exponent to each argument
  {
    const double ex = 729 * m(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    const double ac = m(1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    assert(ex == ac);
  }

  // m(...) applies the constructed exponent to each argument
  {
    const double ex = (1 << 22) * m(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    const double ac = m(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1);
    assert(ex == ac);
  }

  PO_LINE;
}

void evaluate_incomplete()
{
  const po::monomial m{3.2, {0, 1, 6}};
  double y;

  y = m(0.7);
  assert(y != y);

  y = m();
  assert(y != y);

  y = m(3, -0.85);
  assert(y != y);

  PO_LINE;
}

void evaluate_partial()
{
  // Nothing to evaluate
  {
    const po::monomial m{3.2, {0, 1, 6}};
    double y;

    y = m(po::nargs{0});
    assert(y != y);

    PO_LINE;
  }

  // Ignore beyond 1 arg
  {
    const po::monomial m{3.2, {0, 1, 6}};
    double y;

    y = m(po::nargs{1}, 0.7);
    assert(y == 3.2 * 1);

    y = m(po::nargs{1}, 0.7, 2.2, 9.999);
    assert(y == 3.2 * 1);

    PO_LINE;
  }

  // If not enough args, return nan.
  {
    const po::monomial m{3.2, {0, 1, 6}};
    double y;

    y = m(po::nargs{2}, 3);
    assert(y != y);

    y = m(po::nargs{5}, 3, 5.5, 2., -4);
    assert(y != y);

    y = m(po::nargs{8}, 3, 5.5, 2., 0, 0, 0, -4);
    assert(y != y);

    PO_LINE;
  }

  // Ignore beyond 2 args
  {
    const po::monomial m{3.2, {0, 1, 6}};
    double y;

    y = m(po::nargs{2}, 3, -0.85);
    assert(y == 3.2 * 1 * -0.85);

    y = m(po::nargs{2}, 3, -0.85, 9.8, 0.234);
    assert(y == 3.2 * 1 * -0.85);

    PO_LINE;
  }

  {
    po::monomial m{4.3, {3, 2, 1, 0}};
    double t;

    t = m(po::nargs{2}, 2, 5);
    assert(t == 4.3 * 2*2*2 * 5*5);

    t = m(po::nargs{1}, 3);
    assert(t == 4.3 * 3*3*3);

    t = m(po::nargs{0}, 3, 5, 2.2, 4);
    assert(t != t);

    PO_LINE;
  }

}

void evaluate_partial_place_OOR()
{
  po::monomial m{4.3, {3, 2, 1, 0}};
  double t;

  // Ignore pack value beyond nargs.
  // For evaluating antidifferentiation with naive, when place of
  // antidifferentiation is OOR.
  t = m(po::nargs{m.rank()}, 3, 5, 2.2, 4, 5, 72, -0.923);
  assert(t == m(3, 5, 2.2, 4));

  PO_LINE;
}

