#include <iostream>
#include <sstream>

#include "../../types/monomial.h"
#include "../../ostream/monomial_ostream.h"
#include "../macros.h"

#include <cassert>

void test_monomial_ostream()
{
  {
    po::monomial m{po::nan, {4, 3, 6, 6, 1, 3}};

    std::stringstream ss;
    ss << m;

    assert(
      ss.str() == "nan[4,3,6,6,1,3]" ||
      ss.str() == "NaN[4,3,6,6,1,3]" ||
      ss.str() == "NAN[4,3,6,6,1,3]");

    PO_LINE;
  }

  {
    po::monomial m{1.5, {4, 3, 6, 6, 1, 3}};

    std::stringstream ss;
    ss << m;

    assert(ss.str() == "1.5[4,3,6,6,1,3]");

    PO_LINE;
  }

  {
    po::monomial m{1.5, {4, 3, 6, 6, 1, 3}};

    std::stringstream ss;
    po::operator<<(ss, m);

    assert(ss.str() == "1.5[4,3,6,6,1,3]");

    PO_LINE;
  }

  {
    po::monomial m{1.5, {4, 3, 6, 6, 1, 3}};
    std::stringstream ss;

    PO_TRACE_OSTREAM(ss, m);
    assert(ss.str().size() > 0);

    po::scalar_type c;
    ss >> c;
    PO_ASSERT(c == 1.5, c);

    PO_LINE;
  }


}
