#include "../../monomial.h"

#include <iostream>
#include <sstream>
#include <cassert>


#include "../../ostream/monomial_ostream.h"
#include "../../istream/monomial_istream.h"

#include "../macros.h"


using po::operator<<;
using po::operator>>;

void test_monomial0_istream();
void test_monomial1_istream();
void test_monomial2_istream();
void test_monomial_out_in();

void test_monomial_in_out();

void test_monomial_istream()
{
  test_monomial0_istream();
  test_monomial1_istream();
  test_monomial2_istream();

  test_monomial_out_in();
  test_monomial_in_out();

  PO_LINE;
}


// monomial --> string --> monomial
void test_monomial_out_in()
{
  const po::monomial before{81.092, {5, 6, 0, 0, 3, 1, 4}};
  std::stringstream ss;
  ss << before;
  po::monomial after;
  ss >> after;

  assert(after.coefficient == before.coefficient);
  assert((after.exponents == before.exponents).min() == true);
}

// string --> monomial --> string
void test_monomial_in_out()
{
  const std::string before{"0.0354[5,19,4]"};
  po::monomial m;
  std::stringstream ss;
  ss << before;
  ss >> m;

  ss = {};
  ss << m;
  std::string after;
  ss >> after;

  PO_ASSERT(after == before, after);
}

void test_monomial0_istream()
{
  const std::string one_term = "2.4[5, 2, 3, 4]";
  std::stringstream ss{one_term};

  po::monomial m{};

  char left_bracket, right_bracket;

  ss >> m.coefficient >> std::ws;
  PO_ASSERT(ss.peek() == '[', char(ss.peek()));

  ss >> left_bracket >> std::ws;
  PO_ASSERT(std::isdigit(char(ss.peek())), char(ss.peek()));

  ss >> m.exponents >> std::ws;
  PO_ASSERT(ss.peek() == ']', char(ss.peek()));

  ss >> right_bracket >> std::ws;
  PO_ASSERT(ss.eof() || ss.peek() == '+', char(ss.peek()));
}

void test_monomial1_istream()
{
  const std::string one_term = "2.4[5, 2, 3, 4]";
  std::stringstream ss{one_term};

  po::monomial m{};
  ss >> m;

  // std::cout << "m = " << m << std::endl;

  assert(m.coefficient == 2.4);
  PO_ASSERT((m.exponents == decltype(m.exponents){5, 2, 3, 4}).min() == true, m.exponents);
}

void test_monomial2_istream()
{
  const std::string one_term = "3.7[0, 0, 6, 1]";
  std::stringstream ss{one_term};

  po::monomial m{};
  ss >> m;

  // std::cout << "m = " << m << std::endl;

  assert(m.coefficient == 3.7);
  PO_ASSERT((m.exponents == decltype(m.exponents){0, 0, 6, 1}).min() == true, m.exponents);
}


