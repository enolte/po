#include "../../polynomial.h"
#include "compare.h"
#include <cassert>

namespace po
{
  bool operator==(const po::monomial& a, const po::monomial& b)
  {
    return ::operator==(a, b);
  }

  bool operator==(const po::polynomial& a, const po::polynomial& b)
  {
    return
      a.this_rank == b.this_rank &&
      a.total_degree == b.total_degree &&
      equal(a.variable_degrees, b.variable_degrees) &&
      unordered_equal(a.terms, b.terms) &&
      true;
  }
}

void test_assignment()
{
  {
    po::polynomial p{{4.2, {4, 0, 7, 6, 5}}, {5.5, {3, 1, 1, 0, 0}}};

    po::polynomial q = p;

    assert(q == p);
  }

  PO_LINE;
}