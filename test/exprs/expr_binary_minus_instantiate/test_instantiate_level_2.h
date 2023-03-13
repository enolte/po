#include "test_instantiate_p__minus__pos_p.h"         //           x0   -   x1
#include "test_instantiate_p__minus__neg_p.h"         //           x0   -   x1
#include "test_instantiate_c__minus__pos_p.h"         //           x0   -   x1
#include "test_instantiate_c__minus__neg_p.h"         //           x0   -   x1
#include "test_instantiate_pos_p__minus__p.h"         //                        x1   -   x0
#include "test_instantiate_pos_p__minus__c.h"         //                        x1   -   x0
#include "test_instantiate_neg_p__minus__p.h"         //                        x1   -   x0
#include "test_instantiate_neg_p__minus__c.h"         //                        x1   -   x0

namespace expr_binary_minus_instantiate
{
  void test_instantiate_level_2()
  {
    test_instantiate_p__minus__pos_p();               //           x0   -   x1
    test_instantiate_p__minus__neg_p();               //           x0   -   x1
    test_instantiate_c__minus__pos_p();               //           x0   -   x1
    test_instantiate_c__minus__neg_p();               //           x0   -   x1
    test_instantiate_pos_p__minus__p();               //                        x1   -   x0
    test_instantiate_pos_p__minus__c();               //                        x1   -   x0
    test_instantiate_neg_p__minus__p();               //                        x1   -   x0
    test_instantiate_neg_p__minus__c();               //                        x1   -   x0
  }

}