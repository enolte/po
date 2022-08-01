#include "../../polynomial.h"

#include <cassert>

template<typename Rank>
void test_instantiate_p_mult_Dp(const po::polynomial& p, const po::polynomial& q, po::polynomial ex);

void test_instantiate_p_mult_Dp()
{
  {
    po::polynomial p{{2, {0, 0}}, {3, {0, 0}}};
    po::polynomial q{{4, {0, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(q * po::D(p, 0), po::rank<2>{});

    test_instantiate_p_mult_Dp<po::rank<2>>(
      p, q,
      {
        {0, {0, 0}},
      });
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(q * po::D(p, 0), po::rank<2>{});

    test_instantiate_p_mult_Dp<po::rank<2>>(
      p, q,
      {
        {40, {5, 1}},
        {10, {4, 1}},
        {24, {2, 2}},
        { 6, {1, 2}}
      });
  }

  {
    po::polynomial q{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial p{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(q * po::D(p, 0), po::rank<2>{});
/*

   {2, {5, 1}}, {3, {2, 2}}
*
   {4, {0, 0}}, {0, {0, 0}}
=
   {8, {5, 1}}, {0, {5, 1}}, {12, {2, 2}}, {0 {2, 2}}

*/
    // TODO
    test_instantiate_p_mult_Dp<po::rank<2>>(
      p, q,
      {
        { 8, {5, 1}},
        // { 0, {5, 1}},
        {12, {2, 2}},
        // { 0, {2, 2}}
      });
  }


  PO_LINE;
}

template<typename Rank>
void test_instantiate_p_mult_Dp(const po::polynomial& p, const po::polynomial& q, po::polynomial ex)
{
  const po::polynomial ac = po::instantiate(q * po::D(p, 0), Rank{});

  PO_ASSERT(unordered_equal(ac.terms, ex.terms), ac);
}


