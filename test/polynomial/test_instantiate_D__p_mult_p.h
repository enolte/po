#include "../../polynomial.h"

#include <cassert>

template<typename Rank>
void test_instantiate_D__p_mult_p(const po::polynomial& p, const po::polynomial& q, po::polynomial ex);

void test_instantiate_D__p_mult_p()
{
  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p * q, 0), po::rank<2>{});

    test_instantiate_D__p_mult_p<po::rank<2>>(p, q,
      {
        {48, {5, 1}},
        {10, {4, 1}},
        // { 0, {5, 1}},
        {36, {2, 2}},
        { 6, {1, 2}},
        // { 0, {2, 2}}
      });

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {48, {5, 1}},
        {10, {4, 1}},
        // { 0, {5, 1}},
        {36, {2, 2}},
        { 6, {1, 2}},
        // { 0, {2, 2}}
      }),
      r);
  }

  PO_LINE;
}

template<typename Rank>
void test_instantiate_D__p_mult_p(const po::polynomial& p, const po::polynomial& q, po::polynomial ex)
{
  const po::polynomial ac = po::instantiate(po::D(p * q, 0), Rank{});

  PO_ASSERT(unordered_equal(ac.terms, ex.terms), ac);
}


