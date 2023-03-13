#include "test_instantiate_neg__neg_p.h"          // -x1
#include "test_instantiate_neg__pos_p.h"          // -x1
#include "test_instantiate_neg__c_minus_p.h"      // -x1
#include "test_instantiate_neg__p_minus_c.h"      // -x1
#include "test_instantiate_neg__p_minus_p.h"      // -x1
#include "test_instantiate_neg__c_plus_p.h"       // -x1

namespace expr_unary_minus_instantiate
{
  void test_instantiate_level_2()
  {
    test_instantiate_neg__neg_p();                // -x1
    test_instantiate_neg__pos_p();                // -x1
    test_instantiate_neg__c_minus_p();            // -x1
    test_instantiate_neg__p_minus_c();            // -x1
    test_instantiate_neg__p_minus_p();            // -x1
    test_instantiate_neg__c_plus_p();             // -x1
  }

}
