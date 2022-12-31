#include "../../ostream/valarray_ostream.h"

#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_instantiate_DIp_instantiate_case3_different_interval();
void test_instantiate_DIp_instantiate_case3();
void test_instantiate_DIp_instantiate_case2();
void test_instantiate_DIp_instantiate_case1();
void test_instantiate_DIp_instantiate_case1_extraneous_variable();

void test_instantiate_DIp()
{
  test_instantiate_DIp_instantiate_case1();
  test_instantiate_DIp_instantiate_case1_extraneous_variable();

  test_instantiate_DIp_instantiate_case2();
  test_instantiate_DIp_instantiate_case3();
  test_instantiate_DIp_instantiate_case3_different_interval();

  PO_LINE;
}

namespace po
{
  template<expression E1>
  constexpr expr_integral<E1> I(E1&& expr, parametric_interval&& i)
  {
    return integral(std::forward<E1>(expr), std::forward<parametric_interval>(i));
  }

  template<expression E1>
  constexpr expr_integral<E1> I(E1&& expr, const parametric_interval& i)
  {
    return integral(std::forward<E1>(expr), i);
  }}

/*
  Case 1: p(x, y) := x + y

  I(x) := I(p, y in [-1, 2]) = 3x + 3/2, with rank 1

  D(I(x), 0) = 3 (= 3*x**0), with rank 1
 */
void test_instantiate_DIp_instantiate_case1()
{
  po::polynomial p{{1, {1, 0}}, {1, {0, 1}}};

  const auto d0i1p = D(integral(p, {1, {-1, 2}}), 0);
  PO_ASSERT(po::expr_rank(d0i1p) == 1, po::expr_rank(d0i1p));

  po::polynomial d0i1p_i = instantiate(d0i1p);
  PO_ASSERT(d0i1p_i.rank() == 1, d0i1p_i.rank());

  PO_ASSERT(unordered_equal(
    d0i1p_i.terms,
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
void test_instantiate_DIp_instantiate_case1_extraneous_variable()
{
  po::polynomial p{{1, {1, 0, 0}}, {1, {0, 1, 0}}};
// PO_TRACE("p       = " << p);

  /*
    D(I, 0)(y, z) = 3
   */
  const auto d0i0p = D(integral(p, {0, {-1, 2}}), 0);
// PO_TRACE("i0p_i   = " << instantiate(integral(p, {0, {-1, 2}})));

  po::polynomial d0i0p_i = instantiate(d0i0p);
// PO_TRACE("d0i0p_i = " << d0i0p_i);

  PO_ASSERT(po::expr_rank(d0i0p) == 2, po::expr_rank(d0i0p));

  PO_ASSERT(d0i0p_i.rank() == 2, d0i0p_i.rank());
  PO_ASSERT(unordered_equal(
    d0i0p_i.terms,
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
  PO_ASSERT(unordered_equal(
    d1i0p_i.terms,
    {
      {0, {0, 0}},
      {0, {1, 0}},
    }),
    d1i0p_i);
}


/*
  Case 2: p(x, y, z) = xy + yz

  For the interval [-1, 2],

    integral(xy + yz, (x, y) in [-1, 2] x [-1, 2] = 2.25 + 4.5z, with rank 1

  or

    I(z) := integral(integral(p, 0), 1)(z) = 2.25 + 4.5z, with rank 1

    D(I, 0)(z) = 4.5, with rank 1
*/
void test_instantiate_DIp_instantiate_case2()
{
  po::polynomial p{{1, {1, 1, 0}}, {1, {0, 1, 1}}};

  const auto i1i0p = integral(integral(p, {0, {-1, 2}}), {0, {-1, 2}});

  const auto d0i1i0p = D(i1i0p, 0);

  po::polynomial d0i1i0p_i = po::instantiate(d0i1i0p);

  PO_ASSERT(d0i1i0p_i.rank() == 1, d0i1i0p_i.rank());
  PO_ASSERT(unordered_equal(
    d0i1i0p_i.terms,
    {
      {0  , {0}},
      {4.5, {0}},
    }),
    d0i1i0p_i);
}

/*
 Case 3: p(x, y, z) = 2*x*y*z + 5 * x**3 * y**2 * z**4

 For the interval J := [-1, 2],

  I(z) := integral(p, (x, y) in J x J)(z) = (9/2)*z + (225/4)*z**4, with rank 1

  D(I, 0)(z) = 9/2 + 225z**3, with rank 1
*/
void test_instantiate_DIp_instantiate_case3()
{
  const po::parametric_interval J0 = {0, {-1, 2}};

  po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};

  const auto iip= integral(integral(p, J0), J0);
  PO_ASSERT(po::expr_rank(iip) == 1, po::expr_rank(iip));

  po::polynomial d0iip_i = po::instantiate(D(iip, 0));

  PO_ASSERT(unordered_equal(
    d0iip_i.terms,
    {
      {  4.5, {0}},
      {225  , {3}}
    }),
    d0iip_i);
}


/*
 Case 3 (different interval): p(x, y, z) = 2*x*y*z + 5 * x**3 * y**2 * z**4

 For the interval J := [-1, 3],

  I(z) = integral(p, (x, y) in J x J)(x) = 32*z + (2800./3)*z**4, with rank 1

  D(I, 0)(z) = 32 + (11200/3)z**3, with rank 1
*/
void test_instantiate_DIp_instantiate_case3_different_interval()
{
  const po::parametric_interval J = {0, {-1, 3}};

  po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};

  po::polynomial diip_i = po::instantiate(D(I(I(p, J), J), 0));

  PO_ASSERT(diip_i.rank() == 1, diip_i.rank());

  PO_ASSERT(unordered_near_rel(
    diip_i.terms,
    {
      {      32, {0}},
      {11200./3, {3}}
    }),
    diip_i);
}

