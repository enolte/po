#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_A__p_mult_p_place1_rank2();
void test_instantiate_A__p_mult_p_place2_rank3();
void test_instantiate_A__p_mult_p_place3_rank5();

void test_instantiate_A__p_mult_p()
{
  test_instantiate_A__p_mult_p_place1_rank2();
  test_instantiate_A__p_mult_p_place2_rank3();
  test_instantiate_A__p_mult_p_place3_rank5();
}


void test_instantiate_A__p_mult_p_place2_rank3()
{
  {
    po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};

    po::polynomial a2_pp = A(p*p, 2);

    PO_ASSERT(compare::unordered_near_rel_terms(
      a2_pp,
      {
        { 4./3, {2, 2, 3}},
        {20./6, {4, 3, 6}},
        {25./9, {6, 4, 9}},
      }),
      a2_pp);

    PO_LINE;

    assert(a2_pp.rank() == 3);
    assert(a2_pp.degree() == 19);
    assert(compare::equal(a2_pp.degrees(), {6, 4, 9}));
  }


  {
    po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};

    po::polynomial a2_pp = A(p*p, 1);

    PO_ASSERT(compare::unordered_near_rel_terms(
      a2_pp,
      {
        { 4./3, {2, 3, 2}},
        {20./4, {4, 4, 5}},
        {25./5, {6, 5, 8}},
      }),
      a2_pp);

    assert(a2_pp.rank() == 3);
    assert(a2_pp.degree() == 19);
    assert(compare::equal(a2_pp.degrees(), {6, 5, 8}));

    PO_LINE;
  }

}


void test_instantiate_A__p_mult_p_place1_rank2()
{

  po::polynomial p{{1, {1, 0}}, {1, {0, 1}}};
  po::polynomial q{{1, {2, 0}}, {2, {1, 1}}};

  const auto ax = A(p * q, 1);
  PO_ASSERT(po::expr_rank(ax) == 2, po::expr_rank(ax));

  po::polynomial ax_i = ax;

  PO_ASSERT(compare::unordered_equal_terms(
    ax_i,
    {
      {1   , {3, 1}},
      {1.5 , {2, 2}},
      {2./3, {1, 3}}
    }),
    ax_i);

  PO_ASSERT(ax_i.rank() == 2, ax_i.rank());
  PO_ASSERT(ax_i.degree() == 4, ax_i.degree());
  PO_ASSERT(compare::equal(ax_i.degrees(), {3, 3}), ax_i.degrees());

  PO_LINE;
}


void test_instantiate_A__p_mult_p_place3_rank5()
{
  po::polynomial p{{1, {1, 0, 3, 2, 1}}, {1, {0, 1, 4, 4, 2}}};
  po::polynomial q{{1, {2, 0, 0, 0, 0}}, {2, {1, 1, 1, 1, 4}}};

// PO_TRACE("   pq = " << p*q);
// PO_TRACE(" a3pq = " << A(p*q, 3));

  const auto ax = A(p * q, 3);

  PO_ASSERT(po::expr_rank(ax) == 5, po::expr_rank(ax));

  po::polynomial a3pq = ax;

  PO_ASSERT(compare::unordered_near_rel_terms(
    a3pq,
    {
      { 1./3, {3, 0, 3, 3, 1}},
      { 1./5, {2, 1, 4, 5, 2}},
      { 0.5 , {2, 1, 4, 4, 5}},
      { 1./3, {1, 2, 5, 6, 6}}
    }),
    a3pq);

  PO_ASSERT(a3pq.rank() == 5, a3pq.rank());
  PO_ASSERT(a3pq.degree() == 20, a3pq.degree());
  PO_ASSERT(compare::equal(a3pq.degrees(), {3, 2, 5, 6, 6}), a3pq.degrees());

  PO_LINE;
}

