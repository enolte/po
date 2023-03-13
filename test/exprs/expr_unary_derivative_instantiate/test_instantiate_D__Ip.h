#include "../../../ostream/valarray_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

#include "../expr_unary_integral_evaluate/I.h"

void test_instantiate_D__Ip_instantiate_case1();
void test_instantiate_D__Ip_instantiate_case1_extraneous_variable();


void test_instantiate_D__Ip()
{
  test_instantiate_D__Ip_instantiate_case1();
  test_instantiate_D__Ip_instantiate_case1_extraneous_variable();

  PO_LINE;
}


/*
  Case 1: p(x, y) := x + y

  I(x) := I(p, y in [-1, 2]) = 3x + 3/2, with rank 1

  D(I(x), 0) = 3 (= 3*x**0), with rank 1
 */
void test_instantiate_D__Ip_instantiate_case1()
{
  po::polynomial p{{1, {1, 0}}, {1, {0, 1}}};

  const auto d0i1p = D(I(p, {1, {-1, 2}}), 0);
  PO_ASSERT(po::expr_rank(d0i1p) == 1, po::expr_rank(d0i1p));

  po::polynomial d0i1p_i = instantiate(d0i1p);
  PO_ASSERT(d0i1p_i.rank() == 1, d0i1p_i.rank());

  PO_ASSERT(compare::unordered_equal_terms(
    d0i1p_i,
    {
      {3, {0}},
      {0, {0}},
    }),
    d0i1p_i);
}

/*
  Case 1(extraneous variable): p(x, y, z) := x + y

  For the interval [-1, 2],

    I(y, z) := integral(p, 0)(y, z) = 3/2 + 3y, with rank 2

    D(I, 0)(y, z) = 3, with rank 2
    D(I, 1)(y, z) = 0, with rank 2

 */
void test_instantiate_D__Ip_instantiate_case1_extraneous_variable()
{
  po::polynomial p{{1, {1, 0, 0}}, {1, {0, 1, 0}}};
// PO_TRACE("p       = " << p);

  /*
    D(I, 0)(y, z) = 3
   */
  const auto d0i0p = D(I(p, {0, {-1, 2}}), 0);
// PO_TRACE("i0p_i   = " << instantiate(integral(p, {0, {-1, 2}})));

  po::polynomial d0i0p_i = instantiate(d0i0p);
// PO_TRACE("d0i0p_i = " << d0i0p_i);

  PO_ASSERT(po::expr_rank(d0i0p) == 2, po::expr_rank(d0i0p));

  PO_ASSERT(d0i0p_i.rank() == 2, d0i0p_i.rank());
  PO_ASSERT(compare::unordered_equal_terms(
    d0i0p_i,
    {
      {3, {0, 0}},
      {0, {0, 0}},
    }),
    d0i0p_i);


  /*
    D(I, 1)(y, z) = 0
   */
  po::polynomial d1i0p_i = instantiate(D(integral(p, {0, {-1, 2}}), 1));
// PO_TRACE("d1i0p_i = " << d1i0p_i);

  PO_ASSERT(d1i0p_i.rank() == 2, d1i0p_i.rank());
  PO_ASSERT(compare::unordered_equal_terms(
    d1i0p_i,
    {
      {0, {0, 0}},
      {0, {1, 0}},
    }),
    d1i0p_i);
}

