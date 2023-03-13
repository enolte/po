#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_expr_integral_integral_p_instantiate();

void test_instantiate_I__Ip()
{
  test_expr_integral_integral_p_instantiate();

  PO_LINE;
}


void test_expr_integral_integral_p_instantiate()
{
  {
    /*
     integral(x + y, [-1, 2] x [-1, 2]) = 9, with rank 0
     */
    po::polynomial p{{1, {1, 0}}, {1, {0, 1}}};

    const auto ip = integral( p, {0, {-1, 2}});
    PO_ASSERT(po::expr_rank(ip) == 1, po::expr_rank(ip));

    const auto iip= integral(ip, {0, {-1, 2}});
    PO_ASSERT(po::expr_rank(iip) == 0, po::expr_rank(iip));

    po::polynomial iip_i = po::instantiate(iip);

    PO_ASSERT(compare::unordered_equal_terms(
      iip_i,
      {
        {4.5 + 4.5, {}},
      }),
      iip_i);

    PO_ASSERT(compare::equal(iip_i.degrees(), {}), iip_i.degrees());
    PO_ASSERT(iip_i.degree() == 0, iip_i.degree());
    PO_ASSERT(iip_i.rank() == 0, iip_i.rank());
  }

  {
    /*
     integral(x + y, [-1, 2] x [-1, 2] x [-1, 2]) = 9 (= 9*z**0), with rank 1
     */
    po::polynomial p{{1, {1, 0, 0}}, {1, {0, 1, 0}}};

    const auto ip = integral( p, {0, {-1, 2}});
    PO_ASSERT(po::expr_rank(ip) == 2, po::expr_rank(ip));

    const auto iip= integral(ip, {0, {-1, 2}});
    PO_ASSERT(po::expr_rank(iip) == 1, po::expr_rank(iip));

    po::polynomial iip_i = po::instantiate(iip);

    PO_ASSERT(compare::unordered_equal_terms(
      iip_i,
      {
        {4.5 + 4.5, {0}},
      }),
      iip_i);

    PO_ASSERT(compare::equal(iip_i.degrees(), {0}), iip_i.degrees());
    PO_ASSERT(iip_i.degree() == 0, iip_i.degree());
    PO_ASSERT(iip_i.rank() == 1, iip_i.rank());
  }

  {
    /*
     integral(xy + yz, (x, y) in [-1, 2] x [-1, 2] = 2.25 + 4.5z, with rank 1
     */
    po::polynomial p{{1, {1, 1, 0}}, {1, {0, 1, 1}}};

    const auto ip = integral( p, {0, {-1, 2}});
    PO_ASSERT(po::expr_rank(ip) == 2, po::expr_rank(ip));

    const auto iip= integral(ip, {0, {-1, 2}});
    PO_ASSERT(po::expr_rank(iip) == 1, po::expr_rank(iip));

    po::polynomial iip_i = po::instantiate(iip);

    PO_ASSERT(compare::unordered_equal_terms(
      iip_i,
      {
        {2.25, {0}},
        {4.5 , {1}},
      }),
      iip_i);

    PO_ASSERT(compare::equal(iip_i.degrees(), {1}), iip_i.degrees());
    PO_ASSERT(iip_i.degree() == 1, iip_i.degree());
    PO_ASSERT(iip_i.rank() == 1, iip_i.rank());
  }

  {
    /*
     p(x, y, z) = 2*x*y*z + 5 * x**3 * y**2 * z**4
     integral(p, (x, y) in [-1, 2] x [-1, 2]) = (9/2)*z + (256/4)*z**4, with rank 1
     */
    po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};

    const auto ip = integral(  p, {0, {-1, 2}});
    PO_ASSERT(po::expr_rank(ip) == 2, po::expr_rank(ip));

    const auto iip= integral(ip, {0, {-1, 2}});
    PO_ASSERT(po::expr_rank(iip) == 1, po::expr_rank(iip));

    po::polynomial iip_i = po::instantiate(iip);

    PO_ASSERT(compare::unordered_equal_terms(
      iip_i,
      {
        { 4.5 , {1}},
        {56.25, {4}}
      }),
      iip_i);

    PO_ASSERT(compare::equal(iip_i.degrees(), {4}), iip_i.degrees());
    PO_ASSERT(iip_i.degree() == 4, iip_i.degree());
    PO_ASSERT(iip_i.rank() == 1, iip_i.rank());
  }

  {
    /*
     p(x, y, z) = 2*x*y*z + 5 * x**3 * y**2 * z**4
     integral(p, (x, y) in [-1, 3] x [-1, 3]) = 32*z + (2800./3)*z**4, with rank 1
     */
    po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};

    const auto ip = integral(  p, {0, {-1, 3}});
    PO_ASSERT(po::expr_rank(ip) == 2, po::expr_rank(ip));

    const auto ip_i = instantiate(ip);
    PO_ASSERT(ip_i.rank() == 2, ip_i.rank());

    po::polynomial iip_i = po::instantiate(integral(ip, {0, {-1, 3}}));

    PO_ASSERT(iip_i.rank() == 1, iip_i.rank());

    PO_ASSERT(compare::unordered_near_rel_terms(
      iip_i,
      {
        {32, {1}},
        {2800./3, {4}}
      }),
      iip_i);

    PO_ASSERT(compare::equal(iip_i.degrees(), {4}), iip_i.degrees());
    PO_ASSERT(iip_i.degree() == 4, iip_i.degree());
    PO_ASSERT(iip_i.rank() == 1, iip_i.rank());
  }

}
