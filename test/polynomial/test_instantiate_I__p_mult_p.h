#include "../../ostream/valarray_ostream.h"

#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_expr_I__p_mult_p_instantiate_place1_rank2();
void test_expr_I__p_mult_p_instantiate_place3_rank5();

void test_instantiate_I__p_mult_p()
{
  test_expr_I__p_mult_p_instantiate_place1_rank2();
  test_expr_I__p_mult_p_instantiate_place3_rank5();

  PO_LINE;
}

/*
  p(x, y) = x + y
  q(x, y) = x**2 + 2*x*y

  (p * q)(x, y) = x**3   +   x**2 * y  +  2 * x**2 * y  +  2 * x * y**2

  integral(p*q, y in [-1, 2]) = 3*x**3  + 9/2*x**2  +  6*x, with rank 1

 */
void test_expr_I__p_mult_p_instantiate_place1_rank2()
{

  po::polynomial p{{1, {1, 0}}, {1, {0, 1}}};

  po::polynomial q{{1, {2, 0}}, {2, {1, 1}}};

  const auto ix = integral(p * q, {1, {-1, 2}});
  PO_ASSERT(po::expr_rank(ix) == 1, po::expr_rank(ix));

  po::polynomial ix_i = instantiate(ix);

  PO_ASSERT(unordered_equal_terms(
    ix_i,
    {
      {3  , {3}},
      {4.5, {2}},
      {6  , {1}}
    }),
    ix_i);

  PO_ASSERT(ix_i.rank() == 1, ix_i.rank());
  PO_ASSERT(ix_i.degree() == 3, ix_i.degree());
  PO_ASSERT(equal(ix_i.degrees(), {3}), ix_i.degrees());
}

/*
  p(v, w, x, y, z)           = {1   , {1, 0, 3, 2, 1}} + {1   , {0, 1, 4, 4, 2}}
                             = v * x**3 * y**2 * z   +           w * x**4 * y**4 * z**2

  q(v, w, x, y, z)           = {1   , {2, 0, 0, 0, 0}} + {2   , {1, 1, 1, 1, 4}}
                             = v**2                  +   2 * v * w * x    * y    * z**4


  (p*q)(v, w, x, y, z)       = {1   , {3, 0, 3, 2, 1}} + {1   , {2, 1, 4, 4, 2}} +
                               {2   , {2, 1, 4, 3, 5}} + {2   , {1, 2, 5, 5, 6}}
                             =   v**3 *     x**3 * y**2 * z      +   v**2 * w    * x**4 * y**4 * z**2 +
                               2*v**2 * w * x**4 * y**3 * z**5   +   v    * w**2 * x**4 * y**5 * z**6


  integral(p*q, y in [0, 1]) = {3   , {3, 0, 3,    1}} + {33/5, {2, 1, 4,    2}} +
                               {15/2, {2, 1, 4,    5}} + {21  , {1, 2, 5,    6}}, with rank 4
 */
void test_expr_I__p_mult_p_instantiate_place3_rank5()
{
  po::polynomial p{{1, {1, 0, 3, 2, 1}}, {1, {0, 1, 4, 4, 2}}};
  po::polynomial q{{1, {2, 0, 0, 0, 0}}, {2, {1, 1, 1, 1, 4}}};


  const auto ix = integral(p * q, {3, {-1, 2}});
  PO_ASSERT(po::expr_rank(ix) == 4, po::expr_rank(ix));

  po::polynomial ix_i = instantiate(ix);

  PO_ASSERT(unordered_near_rel_terms(
    ix_i,
    {
      { 3   , {3, 0, 3, 1}},
      { 6.6 , {2, 1, 4, 2}},
      { 7.5 , {2, 1, 4, 5}},
      {21   , {1, 2, 5, 6}}
    }),
    ix_i);

  PO_ASSERT(ix_i.rank() == 4, ix_i.rank());
  PO_ASSERT(ix_i.degree() == 14, ix_i.degree());
  PO_ASSERT(equal(ix_i.degrees(), {3, 2, 5, 6}), ix_i.degrees());

}