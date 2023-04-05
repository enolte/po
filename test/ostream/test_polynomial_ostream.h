#include <iostream>
#include <sstream>

#include "../../polynomial.h"
#include "../../ostream/polynomial_ostream.h"
#include "../macros.h"

#include <cassert>

void test_polynomial_ostream()
{
  {
    std::stringstream ss;
    ss << po::polynomial{};

    assert(ss.str().empty());

    PO_LINE;
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};

    std::stringstream ss;
    ss << p;

    assert(ss.str() == "1.4[2,3,2,1]+0.5[4,1,4,1]");

    PO_LINE;
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};

    std::stringstream ss;
    ss << p << std::endl;

    std::stringstream ss0;
    ss0 << ss.str();
    assert(ss0.str().starts_with("1.4[2,3,2,1]+0.5[4,1,4,1]"));

    PO_LINE;
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};

    std::stringstream ss;
    po::operator<<(ss, p);

    assert(ss.str() == "1.4[2,3,2,1]+0.5[4,1,4,1]");

    PO_LINE;
  }


  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};

    std::stringstream ss;
    PO_TRACE_OSTREAM(ss, p);

    assert(ss.str().starts_with("1.4[2,3,2,1]+0.5[4,1,4,1]"));

    PO_LINE;
  }

}
