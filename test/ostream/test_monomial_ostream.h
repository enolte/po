#include <iostream>
#include <sstream>

#include "../../monomial.h"
#include "../../ostream/monomial_ostream.h"
#include "../macros.h"

#include <cassert>

void test_monomial_ostream()
{
  {
    po::monomial m{1.5, {4, 3, 6, 6, 1, 3}};

    std::stringstream ss;
    ss << m;

    std::cout << ss.str() << std::endl;
  }

  {
    po::monomial m{1.5, {4, 3, 6, 6, 1, 3}};

    std::stringstream ss;
    ss << m << std::endl;

    std::cout << ss.str();
  }

  {
    po::monomial m{1.5, {4, 3, 6, 6, 1, 3}};

    std::stringstream ss;
    po::operator<<(ss, m);

    std::cout << ss.str() << std::endl;
  }

  {
    po::monomial m{1.5, {4, 3, 6, 6, 1, 3}};
    std::stringstream ss;

    PO_TRACE_OSTREAM(ss, m);
    assert(ss.str().size() > 0);

    po::scalar_type c;
    ss >> c;
    PO_ASSERT(c == 1.5, c);
  }

  {
    po::monomial m{1.5, {4, 3, 6, 6, 1, 3}};

    PO_TRACE("m = " << m);
  }
}
