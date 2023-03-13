#include "../../exponents.h"

#include <iostream>
#include <sstream>
#include <cassert>

#include "../macros.h"
#include "../../ostream/valarray_ostream.h"
#include "../../istream/exponents_istream.h"


using po::operator<<;
using po::operator>>;

// cases:                             input:              result:

void test_exponents1_istream();    //  5, 2, 3, 4         stream failbit
void test_exponents2_istream();    //  5, 2, 3, 4]        stream goodbit (success, with no more chars to read)
void test_exponents3_istream();    // [5, 2, 3, 4]        stream failbit
void test_exponents4_istream();    //  5, 2, 3, 4] +      stream goodbit (success, with additional chars to read)

void test_exponents_out_in();
void test_exponents_in_out();

void test_exponents_istream()
{
  test_exponents1_istream();
  test_exponents2_istream();
  test_exponents3_istream();
  test_exponents4_istream();

  test_exponents_out_in();
  test_exponents_in_out();
}

// exponents --> string --> exponents
void test_exponents_out_in()
{
  const po::exponents before{5, 6, 0, 0, 3, 1, 4};
  std::stringstream ss;
  ss << before;
  po::exponents after;
  ss >> after;

  assert((after == before).min() == true);

  PO_LINE;
}

// string --> exponents --> string
void test_exponents_in_out()
{
  const std::string before{"5,2,3,4"};
  std::stringstream ss;
  ss << before;
  po::exponents exponents;
  ss >> exponents;

  ss = {};
  ss << exponents;
  std::string after;
  ss >> after;

  PO_ASSERT(after == before, after);

  PO_LINE;
}


/*
 * No leading '[' and no trailing ']'  -->  fail
 */
void test_exponents1_istream()
{
  const std::string exponents_str = "5, 2, 3, 4";
  std::stringstream ss{exponents_str};

  po::exponents exponents;
  ss >> exponents;
/*
  std::cout << "goodbit = " << std::ios_base::goodbit << std::endl
            << "badbit  = " << std::ios_base::badbit << std::endl
            << "eofbit  = " << std::ios_base::eofbit << std::endl
            << "failbit = " << std::ios_base::failbit << std::endl
            << "state   = " << ss.rdstate() << std::endl;
*/

  assert(ss.fail());

  // PO_TRACE("exponents = " << exponents);
  PO_ASSERT((exponents == decltype(exponents){5, 2, 3, 4}).min() == true, exponents);

  PO_LINE;
}

/*
 * No leading '[' and present trailing ']'  -->  success
 */
void test_exponents2_istream()
{
  const std::string exponents_str = "\v   \f5, 2, \t\t3, 4]";
  std::stringstream ss{exponents_str};
  assert(ss.peek() == '\v');

  po::exponents exponents;

  ss >> exponents;
  assert(ss.good());
  assert(ss.peek() == ']');

  char right_bracket = -1;
  ss >> right_bracket;
  assert(right_bracket == ']');
  assert(ss.good());

  ss >> std::ws;
  assert(ss.eof());

  // PO_TRACE("exponents = " << exponents);
  PO_ASSERT((exponents == decltype(exponents){5, 2, 3, 4}).min() == true, exponents);

  PO_LINE;
}

/*
 * Leading '[' and trailing ']'  -->  fail
 */
void test_exponents3_istream()
{
  const std::string exponents_str = "[  5, 2, \t\t3, 4]";
  std::stringstream ss{exponents_str};

  po::exponents exponents;

  ss >> exponents;
  assert(ss.fail());

  PO_LINE;
}

/*
 * No leading '[' and present ']' and trailing '+'  --> success
 */
void test_exponents4_istream()
{
  const std::string exponents_str = "\v   \f5, 2, \t\t3, 4] + ";
  std::stringstream ss{exponents_str};
  assert(ss.peek() == '\v');

  po::exponents exponents;

  ss >> exponents;
  assert(ss.good());
  assert(ss.peek() == ']');

  char right_bracket = -1;
  ss >> right_bracket;
  assert(right_bracket == ']');
  assert(ss.good());

  ss >> std::ws;
  assert(ss.peek() == '+');
  assert(ss.good());

  // PO_TRACE("exponents = " << exponents);
  PO_ASSERT((exponents == decltype(exponents){5, 2, 3, 4}).min() == true, exponents);

  PO_LINE;
}
