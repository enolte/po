#include "../../ostream/valarray_ostream.h"

#include "../../polynomial.h"

#include "../errors.h"

#include <cassert>

void test_expr_integral_p_instantiate_place1_rank2();
void test_expr_integral_p_instantiate_place0_rank3();
void test_expr_integral_p_instantiate_place1_rank3();
void test_expr_integral_p_instantiate_place2_rank3();
void test_expr_integral_p_instantiate_place3_rank3(); // OOR case: rank(resultant poly) == rank(input poly)

void test_expr_integral_p_instantiate_terms_rank4();

void test_instantiate_Ip()
{
  test_expr_integral_p_instantiate_place1_rank2();
  test_expr_integral_p_instantiate_place0_rank3();
  test_expr_integral_p_instantiate_place1_rank3();
  test_expr_integral_p_instantiate_place2_rank3();
  test_expr_integral_p_instantiate_place3_rank3();

  test_expr_integral_p_instantiate_terms_rank4();

  PO_LINE;
}

void test_expr_integral_p_instantiate_place1_rank2()
{
  /*
   integral(x + y, y in [-1, 2]) = 3x + 3/2, with rank 1
   */
  po::polynomial p{{1, {1, 0}}, {1, {0, 1}}};

  const auto ip = integral( p, {1, {-1, 2}});
  PO_ASSERT(po::expr_rank(ip) == 1, po::expr_rank(ip));

  po::polynomial ip_i = instantiate(ip);
  PO_ASSERT(ip_i.rank() == 1, ip_i.rank());

  PO_ASSERT(unordered_equal(
    ip_i.terms,
    {
      {3  , {1}},
      {1.5, {0}}
    }),
    ip_i);

  PO_ASSERT(ip_i.degree() == 1, ip_i.degree());
  PO_ASSERT(equal(ip_i.degrees(), {1}), ip_i.degrees());
  PO_ASSERT(ip_i.rank() == 1, ip_i.rank());
}

void test_expr_integral_p_instantiate_terms_rank4()
{
  {
    po::polynomial p     {{2, {1, 1, 1, 1}}};

    const auto x = po::integral(p, 2, {1, 3});
    assert(x.place == 2);
    assert(x.a == 1);
    assert(x.b == 3);
  }

  {
    po::polynomial p     {{2, {1, 1, 1, 1}}};
    po::polynomial p2_13 {{8, {1, 1,    1}}}; // integral of p over [1, 3] in place 2

    const auto x = po::integral(p, 2, {1, 3});
    const po::polynomial xp = po::instantiate(x, po::rank<3>{});

    PO_ASSERT(unordered_equal(xp.terms, p2_13.terms), xp);
    assert(&xp.terms != &p2_13.terms);

    PO_ASSERT(xp.degree() == 3, xp.degree());
    PO_ASSERT(equal(xp.degrees(), {1, 1, 1}), xp.degrees());
    PO_ASSERT(xp.rank() == 3, xp.rank());
  }
}

void test_expr_integral_p_instantiate_place3_rank3()
{
  {
    po::polynomial p{{2, {1, 1, 1}}};
    // PO_TRACE(" p = " << p);

    po::polynomial ip = instantiate(integral(p, 3, {0, 2}), po::rank<2>{});
    // PO_TRACE(" integral(p, 3, {0, 2}) = " << ip);

    assert(ip.rank() == 3);
    PO_ASSERT(po::expr_rank(integral(p, 3, {0, 2})) == 3, po::expr_rank(integral(p, 3, {0, 2})));

    PO_ASSERT(unordered_equal(
      ip.terms,
      {
        {4, {1, 1, 1}}
      }),
      ip);

    PO_ASSERT(ip.degree() == 3, ip.degree());
    PO_ASSERT(equal(ip.degrees(), {1, 1, 1}), ip.degrees());
    PO_ASSERT(ip.rank() == 3, ip.rank());
  }
}

void test_expr_integral_p_instantiate_place0_rank3()
{
  {
    po::polynomial p{{2, {1, 1, 1}}};

    auto x = integral(p, 0, {0, 1});
    PO_ASSERT(po::expr_rank(x) == 2, po::expr_rank(x));

    auto ip = instantiate(x, po::rank<2>{});

    PO_ASSERT(ip.rank() == 2, ip.rank());

    PO_ASSERT(unordered_equal(
      ip.terms,
      {
        {1, {1, 1}}
      }),
      ip);

    PO_ASSERT(ip.degree() == 2, ip.degree());
    PO_ASSERT(equal(ip.degrees(), {1, 1}), ip.degrees());
    PO_ASSERT(ip.rank() == 2, ip.rank());
  }

  {
    po::polynomial p{{2, {1, 1, 1}}};

    po::polynomial ip = instantiate(integral(p, 0, {0, 2}), po::rank<2>{});

    PO_ASSERT(ip.rank() == 2, ip.rank());

    PO_ASSERT(unordered_equal(
      ip.terms,
      {
        {4, {1, 1}}
      }),
      ip);

    PO_ASSERT(ip.degree() == 2, ip.degree());
    PO_ASSERT(equal(ip.degrees(), {1, 1}), ip.degrees());
    PO_ASSERT(ip.rank() == 2, ip.rank());
  }

  // Zero result
  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x = integral(p, 0, {-1, 1});
    auto ip = instantiate(x, po::rank<2>{});
    // PO_TRACE(" integral(p, 0, -1, 1) = " << ip);

    PO_ASSERT(unordered_equal(
      ip.terms,
      {
        {0, {1, 1}}
      }),
      ip);

    PO_ASSERT(ip.degree() == 2, ip.degree());
    PO_ASSERT(equal(ip.degrees(), {1, 1}), ip.degrees());
    PO_ASSERT(ip.rank() == 2, ip.rank());
  }

  {
    po::polynomial p{{2, {1, 1, 1}}};
    auto x  = integral(p, 0, {0, 3});
    auto ip = instantiate(x);
    // PO_TRACE(" integral(p, 0, {0, 3}) = " << ip);

    PO_ASSERT(unordered_equal(
      ip.terms,
      {
        {9, {1, 1}}
      }),
      ip);

    PO_ASSERT(ip.degree() == 2, ip.degree());
    PO_ASSERT(equal(ip.degrees(), {1, 1}), ip.degrees());
    PO_ASSERT(ip.rank() == 2, ip.rank());
  }

}

void test_expr_integral_p_instantiate_place1_rank3()
{
  {
    po::polynomial p{{2, {1, 4, 1}}};

    po::polynomial ip = instantiate(integral(p, 1, {0, 2}), po::rank<2>{});
// PO_TRACE(" ** ip = " << ip);
    assert(ip.rank() == 2);

    PO_ASSERT(unordered_equal(
      ip.terms,
      {
        {0.4*32, {1, 1}}
      }),
      ip);

    PO_ASSERT(ip.degree() == 2, ip.degree());
    PO_ASSERT(equal(ip.degrees(), {1, 1}), ip.degrees());
    PO_ASSERT(ip.rank() == 2, ip.rank());
  }

  {
    po::polynomial p{{2, {1, 4, 1}}};

    po::polynomial ip = instantiate(integral(p, 1, {-1, 1}), po::rank<2>{});
// PO_TRACE(" ** ip = " << ip);
    assert(ip.rank() == 2);

    PO_ASSERT(unordered_equal(
      ip.terms,
      {
        {0.4*2, {1, 1}}
      }),
      ip);

    PO_ASSERT(ip.degree() == 2, ip.degree());
    PO_ASSERT(equal(ip.degrees(), {1, 1}), ip.degrees());
    PO_ASSERT(ip.rank() == 2, ip.rank());
  }
}

void test_expr_integral_p_instantiate_place2_rank3()
{
  {
    po::polynomial p{{2, {1, 1, 1}}};

    po::polynomial ip = instantiate(integral(p, 2, {0, 2}), po::rank<2>{});

    assert(ip.rank() == 2);

    PO_ASSERT(unordered_equal(
      ip.terms,
      {
        {4, {1, 1}}
      }),
      ip);

    PO_ASSERT(ip.degree() == 2, ip.degree());
    PO_ASSERT(equal(ip.degrees(), {1, 1}), ip.degrees());
    PO_ASSERT(ip.rank() == 2, ip.rank());
  }

  {
    po::polynomial p{{2, {1, 1, 1}}, {5, {3, 2, 4}}};

    po::polynomial ip = instantiate(integral(p, 2, {0, 2}), po::rank<2>{});

    assert(ip.rank() == 2);

    PO_ASSERT(unordered_equal(
      ip.terms,
      {
        { 4, {1, 1}},
        {32, {3, 2}}
      }),
      ip);

    PO_ASSERT(ip.degree() == 5, ip.degree());
    PO_ASSERT(equal(ip.degrees(), {3, 2}), ip.degrees());
    PO_ASSERT(ip.rank() == 2, ip.rank());
  }
}

