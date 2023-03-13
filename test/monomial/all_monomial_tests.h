#include <cassert>
#include <iostream>
#include <type_traits>
#include <algorithm>
#include <compare>

#include "../errors.h"
#include "../macros.h"
#include "../../ostream/valarray_ostream.h"

#include "../../monomial.h"

void spot_test1();
void spot_test2();

namespace po_test
{
  void all_monomial_tests()
  {
    spot_test1();
    spot_test2();

    std::vector<po::monomial> t;
    // t.push_back(4.3, po::exponents{3, 3, 4});
    // t.push_back(4.3, {3, 3, 4});
    // t.push_back(4.3, 3, 3, 4);
    t.emplace_back(4.3, po::exponents{3, 3, 4});
    // t.emplace_back(4.3, {3, 3, 4});
    // t.emplace_back(4.3, 3, 3, 4);
  }

}



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



void spot_test1()
{
  // 3.2 * x**5 * z * t**6
  const po::monomial m{3.2, {5, 0, 1, 6}};

  assert(0 == (m.exponents <=> po::exponents{5, 0, 1, 6}));

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
    const double y = m(1, 0, 1, 1);
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


void spot_test2()
{
  // 3.2 * x**5 * z * t**6
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

