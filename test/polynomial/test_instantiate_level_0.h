#include "../../polynomial.h"

#include "compare.h"

#include <cassert>

#include "test_instantiate_c.h"
#include "test_instantiate_p.h"

void test_instantiate_level_0()
{
  test_instantiate_c();
  test_instantiate_p();

  PO_LINE;
}
