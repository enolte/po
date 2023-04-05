#include "test_instantiate_A__c.h"          // A(x0)
#include "test_instantiate_A__p.h"          // A(x0)

namespace expr_unary_antiderivative_instantiate
{
  void test_instantiate_level_1()
  {
    test_instantiate_A__c();                // A(x0)
    test_instantiate_A__p();                // A(x0)
  }
}

