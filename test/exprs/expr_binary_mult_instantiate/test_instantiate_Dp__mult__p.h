#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

template<typename Rank>
void test_instantiate_Dp__mult__p(const po::polynomial& p, const po::polynomial& q, po::polynomial ex);

void test_instantiate_Dp__mult__p()
{
  {
    po::polynomial p{{2, {0, 0}}, {3, {0, 0}}};
    po::polynomial q{{4, {0, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0) * q, po::rank<2>{});

    test_instantiate_Dp__mult__p<po::rank<2>>(
      p, q,
      {
        {0, {0, 0}},
      });
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0) * q, po::rank<2>{});

    test_instantiate_Dp__mult__p<po::rank<2>>(
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
    po::polynomial r = po::instantiate(po::D(p, 0) * q, po::rank<2>{});
/*

   {2, {5, 1}}, {3, {2, 2}}
*
   {4, {0, 0}}, {0, {0, 0}}
=
   {8, {5, 1}}, {0, {5, 1}}, {12, {2, 2}}, {0 {2, 2}}

*/
    test_instantiate_Dp__mult__p<po::rank<2>>(
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
void test_instantiate_Dp__mult__p(const po::polynomial& p, const po::polynomial& q, po::polynomial ex)
{
  const po::polynomial ac = po::instantiate(po::D(p, 0) * q, Rank{});

  PO_ASSERT(compare::unordered_equal_terms(ac, ex.terms), ac);
}


