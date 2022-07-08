#include <iostream>
#include <sstream>

#include "../../polynomial.h"
#include "../../ostream/polynomial_ostream.h"
#include "../macros.h"

#include <cassert>

void test_polynomial_ostream()
{
  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};

    std::stringstream ss;
    ss << p;

    std::cout << ss.str() << std::endl;
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};

    std::stringstream ss;
    ss << p << std::endl;

    std::cout << ss.str();
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};

    std::stringstream ss;
    ::operator<<(ss, p);

    std::cout << ss.str() << std::endl;
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};
    std::stringstream ss;

    PO_TRACE_OSTREAM(ss, p);
    assert(ss.str().size() > 0);

    po::scalar_type c;
    ss >> c;
    PO_ASSERT(c == 1.4, c);
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}, {0.5, {4, 1, 4, 1}}};

    PO_TRACE("p = " << p);
  }
}
