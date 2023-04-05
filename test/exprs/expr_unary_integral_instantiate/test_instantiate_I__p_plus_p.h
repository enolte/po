#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_expr_I__p_plus_p_instantiate_place1_rank2();
void test_expr_I__p_plus_p_instantiate_place2_rank3();
void test_expr_I__p_plus_p_instantiate_place3_rank5();

void test_instantiate_I__p_plus_p()
{
  test_expr_I__p_plus_p_instantiate_place1_rank2();
  test_expr_I__p_plus_p_instantiate_place2_rank3();
  test_expr_I__p_plus_p_instantiate_place3_rank5();
}


void test_expr_I__p_plus_p_instantiate_place2_rank3()
{
  {
    po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};
    po::polynomial q{{2, {1, 2, 1}}, {5, {1, 1, 1}}};
    po::polynomial sum = po::instantiate(p + q, po::rank<3>{});

    PO_ASSERT(compare::unordered_equal_terms(
      sum,
      {
        { 7, {1, 1, 1}},
        { 2, {1, 2, 1}},
        { 5, {3, 2, 4}},
      }),
      sum);

    // l-value source expr
    po::polynomial x_sum_1 = instantiate(po::integral(sum, {2, {0, 2}}), po::rank<2>{});
    assert(x_sum_1.rank() == 2);

    // TODO
    // r-value source expr
    // po::polynomial x_sum_2 = instantiate(po::integral(p + q, 2, {0, 2}), po::rank<2>{});
    // assert(x_sum_2.rank() == 2);
    // assert(compare::unordered_equal_terms(x_sum_1, x_sum_2.terms));

    PO_ASSERT(compare::unordered_near_rel_terms(
      x_sum_1,
      {
        { 7 * 2    , {1, 1}},
        { 2 * 2    , {1, 2}},
        { 5 * 32./5, {3, 2}},
      }),
      x_sum_1);

    PO_LINE;
  }
}


/*
  p(x, y) = x + y

  integral(p, y in [-1, 2]) = 3*x + 3/2, with rank 1

  q(x, y) = x**2 + 2*x*y

  integral(q, y in [-1, 2]) = 3x**2 + 3*x, with rank 1
 */
void test_expr_I__p_plus_p_instantiate_place1_rank2()
{

  po::polynomial p{{1, {1, 0}}, {1, {0, 1}}};

  po::polynomial q{{1, {2, 0}}, {2, {1, 1}}};

  const auto ix = integral(p + q, {1, {-1, 2}});
  PO_ASSERT(po::expr_rank(ix) == 1, po::expr_rank(ix));

  po::polynomial ix_i = instantiate(ix);

  PO_ASSERT(compare::unordered_equal_terms(
    ix_i,
    {
      {3  , {2}},
      {6  , {1}},
      {1.5, {0}}
    }),
    ix_i);

  PO_ASSERT(ix_i.rank() == 1, ix_i.rank());
  PO_ASSERT(ix_i.degree() == 2, ix_i.degree());
  PO_ASSERT(compare::equal(ix_i.degrees(), {2}), ix_i.degrees());

  PO_LINE;
}

/*
  p(v, w, x, y, z)         = v * x**3 * y**2 * z   +   w * x**4 * y**4 * z**2
                           = {1   , {1, 0, 3, 2, 1}}, {1   , {0, 1, 4, 4, 2}}

  P(v, w, x, z) =
  integral(p, y in [0, 1]) = 1/3 * v * x**3 * z   +   1/5 * w * x**4 * z**2
                           = {1./3, {1, 0, 3   , 1}}, {1./5, {0, 1, 4   , 2}}, with rank 4

  q(v, w, x, y, z)         = v**2   +   2 * v * w * x * y * z**4
                           = {1, {2, 0, 0, 0, 0}}, {2, {1, 1, 1, 1, 4}}

  Q(v, w, x, z) =
  integral(q, y in [0, 1]) = v**2   +   v * w * x * z**4
                           = {1, {2, 0, 0   , 0}}, {1, {1, 1, 1   , 4}}, with rank 4

 */
void test_expr_I__p_plus_p_instantiate_place3_rank5()
{
  po::polynomial p{{1, {1, 0, 3, 2, 1}}, {1, {0, 1, 4, 4, 2}}};

  /*
   integral(x**2 + 2*x*y, y in [-1, 2]) = 3x**2 + 3*x, with rank 1
   */
  po::polynomial q{{1, {2, 0, 0, 0, 0}}, {2, {1, 1, 1, 1, 4}}};

  const auto ix = integral(p + q, {3, {0, 1}});
  PO_ASSERT(po::expr_rank(ix) == 4, po::expr_rank(ix));

  po::polynomial ix_i = instantiate(ix);

  PO_ASSERT(compare::unordered_equal_terms(
    ix_i,
    {
      {1./3, {1, 0, 3, 1}},
      {1./5, {0, 1, 4, 2}},
      {1   , {2, 0, 0, 0}},
      {1   , {1, 1, 1, 4}}
    }),
    ix_i);

  PO_ASSERT(ix_i.rank() == 4, ix_i.rank());
  PO_ASSERT(ix_i.degree() == 7, ix_i.degree());
  PO_ASSERT(compare::equal(ix_i.degrees(), {2, 1, 4, 4}), ix_i.degrees());

  PO_LINE;
}

