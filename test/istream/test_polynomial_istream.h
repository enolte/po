#include "../../polynomial.h"

#include <iostream>
#include <sstream>
#include <cassert>


#include "../../ostream/polynomial_ostream.h"
#include "../../istream/polynomial_istream.h"

#include "../macros.h"
#include "../compare.h"

using po::operator<<;
using po::operator>>;

using namespace po_test::compare;

void test_polynomial1_istream();
void test_polynomial2_istream();
void test_polynomial3_istream();
void test_polynomial_expr_istream();

void test_polynomial_in_out();
void test_polynomial_out_in();

void test_polynomial_istream()
{
  test_polynomial1_istream();
  test_polynomial2_istream();
  test_polynomial3_istream();

  test_polynomial_out_in();
  test_polynomial_in_out();

  test_polynomial_expr_istream();
}

void test_polynomial_expr_istream()
{
/*
  po::polynomial
    p
    {
      {1, {2, 0, 0}},
      {2, {1, 1, 1}},
      {3, {0, 0, 1}},
    },
    q
    {
      {3,{2, 2}},
      {4,{0, 4}},
    };

  auto x = p + q;

  po::polynomial s = po::instantiate(p + q, po::rank<3>{});

  std::cout << " ** s.terms = " << s << std::endl;
  std::cout << "s(1, 0, 0) = " << s(1, 0, 0) << std::endl;
  std::cout << "s(0, 1, 0) = " << s(0, 1, 0) << std::endl;
  std::cout << "s(0, 0, 1) = " << s(0, 0, 1) << std::endl;
  std::cout << "s(1, 1, 1) = " << s(1, 1, 1) << std::endl;
  std::cout << "s(2, 2, 2) = " << s(2, 2, 2) << std::endl;
*/
}

// polynomial --> string --> polynomial
void test_polynomial_out_in()
{
  const po::polynomial p
  {
    {3, {4, 4, 4, 4, 4, 4, 4, 4, 4}},
    {4, {3, 3, 3, 3, 3, 3, 3, 3, 3}},
    {5, {2, 2, 2, 2, 2, 2, 2, 2, 2}},
    {6, {1, 1, 1, 1, 1, 1, 1, 1, 1}},
  };

  std::stringstream ss;
  ss << p;

  po::polynomial p1{};
  ss >> p1;

  assert(unordered_equal_terms(p, p1));

  PO_LINE;
}

// string --> polynomial --> string
void test_polynomial_in_out()
{
  const std::string before{"71.51[2,31,12,1]+0.000512[14,11,4,190]"};
  std::stringstream ss;
  ss << before;
  po::polynomial p{};
  ss >> p;

  std::string after;
  ss = {};
  ss << p;
  ss >> after;

  PO_ASSERT(after == before, after);

  PO_LINE;
}

void test_polynomial3_istream()
{
  std::stringstream ss{"71.51[2, 31, 12, 1] + 0.000512[14, 11, 4, 190]"};
  po::polynomial p{};
  ss >> p;

  // std::cout << "p = " << p << std::endl;

  PO_ASSERT(unordered_equal_terms(
    p,
    {
      {71.51    , { 2, 31, 12,   1}},
      { 0.000512, {14, 11,  4, 190}},
    }),
    p);


  PO_LINE;
}

void test_polynomial2_istream()
{
  std::stringstream ss{"1.4[2, 3, 2, 1] + 0.5[4, 1, 4, 1]"};
  po::polynomial p{};
  ss >> p;

  // std::cout << "p = " << p << std::endl;

  PO_ASSERT(unordered_equal_terms(
    p,
    {
      {0.5, {4, 1, 4, 1}},
      {1.4, {2, 3, 2, 1}},
    }),
    p);


  PO_LINE;
}

void test_polynomial1_istream()
{
  const std::string terms_str = "2.4[5, 2, 3, 4] + 3.7[0, 0, 6, 1]";
  std::stringstream ss{terms_str};

  po::polynomial p{};
  ss >> p;

  // std::cout << "p = " << p << std::endl;

  PO_ASSERT(unordered_equal_terms(
    p,
    {
      {2.4, {5, 2, 3, 4}},
      {3.7, {0, 0, 6, 1}},
    }),
    p);

  PO_LINE;
}

