#include "../../polynomial.h"

#include <cassert>

void test_sub_eq_init_list()
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
    assert(compare::equal(p.degrees(), 3, 1, 0));

    p -= {{2.5, {1, 0, 0}}};

    assert(p.nterms() == 4);
    assert(p.coefficient(1, 0, 0) == 0);
    assert(compare::equal(p.degrees(), 3, 1, 0));

    p -= {{2.5, {1, 7, 0}}};

    assert(p.nterms() == 5);
    assert(p.coefficient(1, 7, 0) == -2.5);
    assert(compare::equal(p.degrees(), 3, 7, 0));
  }

  {
    // Build polynomial, term-wise.
    po::polynomial k{po::rank<7>{}};
    for(std::size_t i = 0; i < 4; ++i)
      k -= {{double(3*i + 1), {i, i, i, 2*i, 0, 0, i}}};

    assert(k.nterms() == 4);
    PO_ASSERT(unordered_equal(
      k.terms,
      {
        {- 1, {0, 0, 0, 0, 0, 0, 0}},
        {- 4, {1, 1, 1, 2, 0, 0, 1}},
        {- 7, {2, 2, 2, 4, 0, 0, 2}},
        {-10, {3, 3, 3, 6, 0, 0, 3}},
      }),
      k);

    // Subtract a braced-init-list
    k -=
      {
        {-3, {3, 3, 3, 6, 0, 0, 3}},
        {-2, {1, 1, 1, 3, 0, 0, 1}}
      };

    assert(k.nterms() == 5);
    PO_ASSERT(unordered_equal(
      k.terms,
      {
        {-1, {0, 0, 0, 0, 0, 0, 0}},
        {-4, {1, 1, 1, 2, 0, 0, 1}},
        {-7, {2, 2, 2, 4, 0, 0, 2}},
        {-7, {3, 3, 3, 6, 0, 0, 3}},
        { 2, {1, 1, 1, 3, 0, 0, 1}}
      }),
      k);
  }


  PO_LINE;
}

