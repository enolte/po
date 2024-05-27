#include "../../ostream/exponents_ostream.h"
#include "../../polynomial.h"

#include <iostream>
#include "../macros.h"

const auto count = []{ return po::polynomial::construction_count(); };

#define PO_ASSERT_COUNT(n) PO_ASSERT(count() == (n), count() << " before = " << before);

void test_instance_counts__p_plus_x1();
void test_instance_counts__p_x_p();
void test_instance_counts__p_x_c();
void test_instance_counts__p_div_c();

void test_instance_counts()
{
  test_instance_counts__p_x_p();
  test_instance_counts__p_x_c();
  test_instance_counts__p_div_c();
  test_instance_counts__p_plus_x1();
}


void test_instance_counts__p_x_p()
{
  const std::uint64_t before = count();

  po::polynomial p0 = po::zero(7);
  PO_ASSERT_COUNT(before + 1);

  po::polynomial p1 = po::zero(7);
  PO_ASSERT_COUNT(before + 2);

  // No new instantation for an expr type
  auto x = p0 * p1;
  PO_ASSERT_COUNT(before + 2);

  po::polynomial p = p0 * p1;
  PO_ASSERT_COUNT(before + 4);

  PO_LINE;
}

void test_instance_counts__p_x_c()
{
  const std::uint64_t before = count();

  po::polynomial p0 = po::zero(7);
  PO_ASSERT_COUNT(before + 1);

  po::polynomial p = p0 * 6;
  PO_ASSERT_COUNT(before + 3);

  PO_LINE;
}

void test_instance_counts__p_div_c()
{
  const std::uint64_t before = count();

  po::polynomial p0 = po::zero(7);
  PO_ASSERT_COUNT(before + 1);

  po::polynomial p = p0 / 6;
  PO_ASSERT_COUNT(before + 3);

  PO_LINE;
}

void test_instance_counts__p_plus_x1()
{
  const std::uint64_t before = count();

  auto p = po::zero(9);
  auto q = po::zero(9);
  auto r = po::zero(9);
  PO_ASSERT_COUNT(before + 3);

  // No new instantation for an expr type
  auto x = p + q*r;
  PO_ASSERT_COUNT(before + 3);

  po::polynomial y{x};
  PO_ASSERT_COUNT(before + 6);

  PO_LINE;
}