#include "test_instantiate_extend__c.h"          // extend(x0)
#include "test_instantiate_extend__p.h"          // extend(x0)

namespace expr_unary_extend_instantiate
{
  void test_instantiate_level_1()
  {
    test_instantiate_extend__c();                // extend(x0)
    test_instantiate_extend__p();                // extend(x0)
  }
}

