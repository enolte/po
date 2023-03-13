#include "test_instantiate_I__c.h"          // I(x0)
#include "test_instantiate_I__p.h"          // I(x0)
#include "test_instantiate_I__p_variadic_rank_3_3_integrations.h"          // I(x0)
#include "test_instantiate_I__p_variadic_rank_4_2_integrations.h"          // I(x0)

namespace expr_unary_integral_instantiate
{
  void test_instantiate_level_1()
  {
    test_instantiate_I__c();                // I(x0)
    test_instantiate_I__p();                // I(x0)
    test_instantiate_I__p_variadic_rank_3_3_integrations();                // I(x0)
    test_instantiate_I__p_variadic_rank_4_2_integrations();                // I(x0)
  }
}

