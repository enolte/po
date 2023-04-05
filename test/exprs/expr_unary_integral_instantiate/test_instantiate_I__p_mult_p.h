#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_I__p_mult_p_place1_rank2();
void test_instantiate_I__p_mult_p_place2_rank3();
void test_instantiate_I__p_mult_p_place3_rank5();

void test_instantiate_I__p_mult_p()
{
  test_instantiate_I__p_mult_p_place1_rank2();
  test_instantiate_I__p_mult_p_place2_rank3();
  test_instantiate_I__p_mult_p_place3_rank5();
}


void test_instantiate_I__p_mult_p_place2_rank3()
{
  {
    po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};
    po::polynomial p_sq = po::instantiate(p*p, po::rank<3>{});
    po::polynomial x_p_sq_1 = instantiate(po::integral(p_sq, {2, {0, 2}}), po::rank<2>{});
    po::polynomial x_p_sq_2 = instantiate(po::integral(p*p , {2, {0, 2}}), po::rank<2>{});

    assert(x_p_sq_1.rank() == 2);
    assert(x_p_sq_2.rank() == 2);

    assert(compare::unordered_equal_terms(x_p_sq_1, x_p_sq_2));
    PO_ASSERT(compare::unordered_near_rel_terms(
      x_p_sq_1,
      {
        { 4 *   8./3, {2, 2}},
        {20 *  64./6, {4, 3}},
        {25 * 512./9, {6, 4}},
      }),
      x_p_sq_1);

    PO_LINE;
  }
}

void test_instantiate_I__p_mult_p_place1_rank2()
{

  po::polynomial p{{1, {1, 0}}, {1, {0, 1}}};
  po::polynomial q{{1, {2, 0}}, {2, {1, 1}}};

  const auto ix = integral(p * q, {1, {-1, 2}});
  PO_ASSERT(po::expr_rank(ix) == 1, po::expr_rank(ix));

  po::polynomial ix_i = instantiate(ix);

  PO_ASSERT(compare::unordered_equal_terms(
    ix_i,
    {
      {3  , {3}},
      {4.5, {2}},
      {6  , {1}}
    }),
    ix_i);

  PO_ASSERT(ix_i.rank() == 1, ix_i.rank());
  PO_ASSERT(ix_i.degree() == 3, ix_i.degree());
  PO_ASSERT(compare::equal(ix_i.degrees(), {3}), ix_i.degrees());

  PO_LINE;
}

void test_instantiate_I__p_mult_p_place3_rank5()
{
  po::polynomial p{{1, {1, 0, 3, 2, 1}}, {1, {0, 1, 4, 4, 2}}};
  po::polynomial q{{1, {2, 0, 0, 0, 0}}, {2, {1, 1, 1, 1, 4}}};


  const auto ix = integral(p * q, {3, {-1, 2}});
  PO_ASSERT(po::expr_rank(ix) == 4, po::expr_rank(ix));

  po::polynomial ix_i = instantiate(ix);

  PO_ASSERT(compare::unordered_near_rel_terms(
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
  PO_ASSERT(compare::equal(ix_i.degrees(), {3, 2, 5, 6}), ix_i.degrees());

  PO_LINE;
}

