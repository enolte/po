#include "test_instantiate_p__plus__p.h"      // x0 +     x0
#include "test_instantiate_p__plus__c.h"      // x0 +     x0
#include "test_instantiate_c__plus__p.h"      // x0 +     x0

namespace expr_binary_plus_instantiate
{
  void test_instantiate_level_1()
  {
    test_instantiate_p__plus__p();            // x0 +     x0
    test_instantiate_p__plus__c();            // x0 +     x0
    test_instantiate_c__plus__p();            // x0 +     x0
  }

}