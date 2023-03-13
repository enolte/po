#include "test_instantiate_p__minus__p.h"       // x0   -   x0
#include "test_instantiate_p__minus__c.h"       // x0   -   x0
#include "test_instantiate_c__minus__p.h"       // x0   -   x0

namespace expr_binary_minus_instantiate
{
  void test_instantiate_level_1()
  {
    test_instantiate_p__minus__p();             // x0   -   x0
    test_instantiate_p__minus__c();             // x0   -   x0
    test_instantiate_c__minus__p();             // x0   -   x0
  }

}