#include "../../polynomial.h"

#include "compare.h"

#include <cassert>

void test_instantiate_c_mult_p_plus_p_mult_p_minus_p()
{
  {
    po::polynomial r{po::rank<3>{}}, q{po::rank<3>{}};

    po::polynomial p = po::instantiate(2*r + q*(r-q), po::rank<3>{});

    PO_ASSERT(unordered_equal(
      p.terms,
      {}),
      p.terms);
  }

  {
    po::polynomial
      r{{2, {2, 1, 2}}, {3, {4, 0, 1}}, {5, {0, 0, 1}}},
      q{{2, {2, 1, 2}}, {3, {4, 0, 1}}, {5, {0, 0, 1}}};

    po::polynomial p = po::instantiate(2*r + q*(r-q), po::rank<3>{});

    PO_ASSERT(unordered_equal(
      p.terms,
      {
        { 4, {2, 1, 2}},
        { 6, {4, 0, 1}},
        {10, {0, 0, 1}},
        { 0, {4, 2, 4}},
        { 0, {6, 1, 3}},
        { 0, {2, 1, 3}},
        { 0, {8, 0, 2}},
        { 0, {4, 0, 2}},
        { 0, {0, 0, 2}},
      }),
      p.terms);

  }

  {
    po::polynomial
      r{{2, {1, 0, 0}}, { 3, {0, 1, 0}}, { 5, {0, 0, 1}}},
      q{{7, {1, 0, 0}}, {11, {0, 1, 0}}, {13, {0, 0, 1}}};

    po::polynomial p = po::instantiate(2*r + q*(r-q), po::rank<3>{});

    PO_ASSERT(unordered_equal(
      p.terms,
      {
        {  4 , {1, 0, 0}},
        {  6 , {0, 1, 0}},
        { 10 , {0, 0, 1}},
        {-35 , {2, 0, 0}},
        {-111, {1, 1, 0}},
        {-121, {1, 0, 1}},
        {-88 , {0, 2, 0}},
        {-192, {0, 1, 1}},
        {-104, {0, 0, 2}},
      }),
      p.terms);

  }

  {
    po::polynomial
      r{{2, {2, 1, 2}}, {3, {4, 0, 1}}, {5, {0, 0, 1}}},
      q{{1, {2, 1, 2}}, {1, {4, 0, 1}}, {1, {0, 0, 1}}};

    po::polynomial p = po::instantiate(2*r + q*(r-q), po::rank<3>{});

    PO_ASSERT(unordered_equal(
      p.terms,
      {
        { 4, {2, 1, 2}},
        { 6, {4, 0, 1}},
        {10, {0, 0, 1}},
        { 1, {4, 2, 4}},
        { 3, {6, 1, 3}},
        { 5, {2, 1, 3}},
        { 2, {8, 0, 2}},
        { 6, {4, 0, 2}},
        { 4, {0, 0, 2}}
      }),
      p.terms);

  }

  PO_LINE;
}
