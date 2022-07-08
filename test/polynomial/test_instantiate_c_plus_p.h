#include "../../polynomial.h"

#include <cassert>

void test_instantiate_c_plus_p()
{

  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(-4 + p, po::rank<1>{});

    assert(unordered_equal(
      r.terms,
      {
        {2, {0}}
      }));
  }

  {
    po::polynomial p{{6, {0, 2}}, {3, {1, 1}}};
    po::polynomial r = po::instantiate(-4 + p, po::rank<2>{});

    assert(unordered_equal(
      r.terms,
      {
        { 6, {0, 2}},
        { 3, {1, 1}},
        {-4, {0, 0}}
      }));
  }

  PO_LINE;
}