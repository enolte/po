#include "../../polynomial.h"
#include "../../ops/change_rank.h"
#include "../compare.h"

void test_change_rank()
{
  using namespace po::detail;

  {
    po::polynomial p
    {
      { 0.0, {0, 0, 0}},
      { 2.5, {1, 0, 0}},
      { 3.5, {1, 0, 1}},
      {-3.5, {2, 2, 2}}
    };

    increase_rank(p, 5);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 0.0, {0, 0, 0, 0, 0}},
        { 2.5, {1, 0, 0, 0, 0}},
        { 3.5, {1, 0, 1, 0, 0}},
        {-3.5, {2, 2, 2, 0, 0}}
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p
    {
      { 0.0, {0, 0, 11}},
      { 2.5, {1, 0, 7}},
      { 3.5, {1, 0, 1}},
      {-3.5, {2, 2, 2}}
    };

    increase_rank(p, 7);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 0.0, {0, 0,11, 0, 0, 0, 0}},
        { 2.5, {1, 0, 7, 0, 0, 0, 0}},
        { 3.5, {1, 0, 1, 0, 0, 0, 0}},
        {-3.5, {2, 2, 2, 0, 0, 0, 0}}
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p
    {
      { 0.0, {0, 0,11, 0, 0, 0, 0}},
      { 2.5, {1, 0, 7, 0, 0, 0, 0}},
      { 3.5, {1, 0, 1, 0, 0, 0, 0}},
      {-3.5, {2, 2, 2, 0, 0, 0, 0}}
    };

    decrease_rank(p, 3);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 0.0, {0, 0,11, 0, 0, 0}},
        { 2.5, {1, 0, 7, 0, 0, 0}},
        { 3.5, {1, 0, 1, 0, 0, 0}},
        {-3.5, {2, 2, 2, 0, 0, 0}}
      }),
      p);

    PO_LINE;
  }

  {
    po::polynomial p
    {
      { 0.0, {0, 0,11, 0, 0, 0, 0}},
      { 2.5, {1, 0, 7, 0, 0, 0, 0}},
      { 3.5, {1, 0, 1, 0, 0, 0, 0}},
      {-3.5, {2, 2, 2, 0, 0, 0, 0}}
    };

    decrease_rank(p, 2);

    // Matching multiindices after reduction are auto-combined
    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        { 0.0, {0, 0, 0, 0, 0, 0}},
        { 6  , {1, 0, 0, 0, 0, 0}},
        {-3.5, {2, 2, 0, 0, 0, 0}}
      }),
      p);

    PO_LINE;
  }
}

