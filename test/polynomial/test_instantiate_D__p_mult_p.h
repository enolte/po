#include "../../polynomial.h"

#include <cassert>

void test_instantiate_D__p_mult_p()
{
  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p * q, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {48, {5, 1}},
        {10, {4, 1}},
        {36, {2, 2}},
        { 6, {1, 2}},
      }),
      r);
  }

  {
    // Zero terms are preserved
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {10, {0, 0}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p * q, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {48, {5, 1}},
        {10, {4, 1}},
        {36, {2, 2}},
        { 6, {1, 2}},
        {40, {0, 0}},
        { 0, {0, 0}},
      }),
      r.terms);
  }

  {
    // Distinct but algebraically equivalent to the above.
    // Note that the terms on not identical, but they are evaluation-identical.
    // Zero terms are preserved.
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {10, {0, 0}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0) * q   +   p * po::D(q, 0), po::rank<2>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {48, {5, 1}},
        {10, {4, 1}},
        {36, {2, 2}},
        { 6, {1, 2}},
        {40, {0, 0}},
        { 0, {1, 0}},
      }),
      r.terms);
  }


  PO_LINE;
}

