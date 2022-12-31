#include "../../polynomial.h"

#include "test_instantiate_level_0.h"
#include "test_instantiate_level_1.h"
#include "test_instantiate_level_2.h"
#include "test_instantiate_level_3.h"
#include "test_instantiate_level_4.h"

void test_instantiate()
{
  test_instantiate_level_0();
  test_instantiate_level_1();
  test_instantiate_level_2();
  test_instantiate_level_3();
  test_instantiate_level_4();

  PO_LINE;
}
