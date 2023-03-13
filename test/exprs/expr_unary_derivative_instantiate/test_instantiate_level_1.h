#include "test_instantiate_D__c.h"              // D(x0)
#include "test_instantiate_D__p.h"              // D(x0)

namespace expr_unary_derivative_instantiate
{
  void test_instantiate_level_1()
  {
    test_instantiate_D__c();                    // D(x0)
    test_instantiate_D__p();                    // D(x0)
  }
}
