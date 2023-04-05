#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

#include "../expr_unary_integral_evaluate/I.h"

void test_instantiate_D__IIp_instantiate_case2();
void test_instantiate_D__IIp_instantiate_case3();
void test_instantiate_D__IIp_instantiate_case3_different_interval();

void test_instantiate_D__IIp()
{
  test_instantiate_D__IIp_instantiate_case2();
  test_instantiate_D__IIp_instantiate_case3();
  test_instantiate_D__IIp_instantiate_case3_different_interval();
}

/*
  Case 2: p(x, y, z) = xy + yz

  For the interval [-1, 2],

    integral(xy + yz, (x, y) in [-1, 2] x [-1, 2] = 2.25 + 4.5z, with rank 1

  or

    I(z) := integral(integral(p, 0), 1)(z) = 2.25 + 4.5z, with rank 1

    D(I, 0)(z) = 4.5, with rank 1
*/
void test_instantiate_D__IIp_instantiate_case2()
{
  po::polynomial p{{1, {1, 1, 0}}, {1, {0, 1, 1}}};

  const auto i1i0p = I(I(p, {0, {-1, 2}}), {0, {-1, 2}});

  const auto d0i1i0p = D(i1i0p, 0);

  po::polynomial d0i1i0p_i = po::instantiate(d0i1i0p);

  PO_ASSERT(d0i1i0p_i.rank() == 1, d0i1i0p_i.rank());
  PO_ASSERT(compare::unordered_equal_terms(
    d0i1i0p_i,
    {
      {0  , {0}},
      {4.5, {0}},
    }),
    d0i1i0p_i);

  PO_LINE;
}

/*
 Case 3: p(x, y, z) = 2*x*y*z + 5 * x**3 * y**2 * z**4

 For the interval J := [-1, 2],

  I(z) := integral(p, (x, y) in J x J)(z) = (9/2)*z + (225/4)*z**4, with rank 1

  D(I, 0)(z) = 9/2 + 225z**3, with rank 1
*/
void test_instantiate_D__IIp_instantiate_case3()
{
  const po::parametric_interval J = {0, {-1, 2}};

  po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};

  const auto iip= I(I(p, J), J);
  PO_ASSERT(po::expr_rank(iip) == 1, po::expr_rank(iip));

  po::polynomial d0iip_i = po::instantiate(D(iip, 0));

  PO_ASSERT(compare::unordered_equal_terms(
    d0iip_i,
    {
      {  4.5, {0}},
      {225  , {3}}
    }),
    d0iip_i);

  PO_LINE;
}


/*
 Case 3 (different interval): p(x, y, z) = 2*x*y*z + 5 * x**3 * y**2 * z**4

 For the interval J := [-1, 3],

  I(z) = integral(p, (x, y) in J x J)(x) = 32*z + (2800./3)*z**4, with rank 1

  D(I, 0)(z) = 32 + (11200/3)z**3, with rank 1
*/
void test_instantiate_D__IIp_instantiate_case3_different_interval()
{
  const po::parametric_interval J = {0, {-1, 3}};

  po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};

  po::polynomial diip_i = po::instantiate(D(I(I(p, J), J), 0));

  PO_ASSERT(diip_i.rank() == 1, diip_i.rank());

  PO_ASSERT(compare::unordered_near_rel_terms(
    diip_i,
    {
      {      32, {0}},
      {11200./3, {3}}
    }),
    diip_i);

  PO_LINE;
}

