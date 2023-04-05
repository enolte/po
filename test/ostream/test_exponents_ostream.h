#include <iostream>
#include <sstream>

#include "../../types/exponents.h"
#include "../../ostream/exponents_ostream.h"
#include "../macros.h"

#include <cassert>

using po::operator<<;

void test_exponents_ostream()
{
  po::exponents x{4, 3, 6, 6, 1, 3};

  std::stringstream ss;
  ss << x;

  assert(ss.str() == "4,3,6,6,1,3");

  PO_LINE;
}
