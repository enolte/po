#include "test_instantiate_p__mult__p.h"      // x0     * x0
#include "test_instantiate_p__mult__c.h"      // x0     * x0
#include "test_instantiate_c__mult__p.h"      // x0     * x0

namespace expr_binary_mult_instantiate
{
  void test_instantiate_level_1()
  {
    test_instantiate_p__mult__p();              // x0     * x0
    test_instantiate_p__mult__c();              // x0     * x0
    test_instantiate_c__mult__p();              // x0     * x0
  }
}

