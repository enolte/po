#include "test_instantiate_p__plus__pos_p.h"        //           x0 +     x1
#include "test_instantiate_p__plus__neg_p.h"        //           x0 +     x1
#include "test_instantiate_c__plus__pos_p.h"        //           x0 +     x1
#include "test_instantiate_c__plus__neg_p.h"        //           x0 +     x1

#include "test_instantiate_p__plus__p_plus_p.h"     //           x0 +     x1
#include "test_instantiate_p_plus_p__plus__p.h"     //           x1 +     x0
#include "test_instantiate_p__plus__p_plus_c.h"     //           x0 +     x1
#include "test_instantiate_p_plus_p__plus__c.h"     //           x1 +     x0
#include "test_instantiate_p__plus__c_plus_p.h"     //           x0 +     x1
#include "test_instantiate_p_plus_c__plus__p.h"     //           x1 +     x0
#include "test_instantiate_p_plus_c__plus__c.h"     //           x1 +     x0

#include "test_instantiate_c__plus__c_plus_p.h"     //           x0 +     x1
#include "test_instantiate_c__plus__p_plus_p.h"     //           x0 +     x1
#include "test_instantiate_c_plus_p__plus__p.h"     //           x1 +     x0

#include "test_instantiate_pos_p__plus__p.h"        //                        x1 +     x0
#include "test_instantiate_pos_c__plus__p.h"        //           x1 +     x0
#include "test_instantiate_pos_p__plus__c.h"        //                        x1 +     x0
#include "test_instantiate_neg_p__plus__p.h"        //                        x1 +     x0
#include "test_instantiate_neg_c__plus__p.h"        //           x1 +     x0
#include "test_instantiate_neg_p__plus__c.h"        //                        x1 +     x0


#include "test_instantiate_p__plus__Dp.h"           // x0 +     D(x0)
#include "test_instantiate_p__plus__Ip.h"           // x0 +     I(x0)

#include "test_instantiate_Dp__plus__p.h"           // D(x0) +  x0

namespace expr_binary_plus_instantiate
{
  void test_instantiate_level_2()
  {
    test_instantiate_pos_c__plus__p();                //           x1 +     x0
    test_instantiate_neg_c__plus__p();                //           x1 +     x0

    test_instantiate_p__plus__pos_p();                //           x0 +     x1
    test_instantiate_p__plus__neg_p();                //           x0 +     x1
    test_instantiate_c__plus__pos_p();                //           x0 +     x1
    test_instantiate_c__plus__neg_p();                //           x0 +     x1

    test_instantiate_p__plus__p_plus_p();             //           x0 +     x1
    test_instantiate_p__plus__p_plus_c();             //           x0 +     x1
    test_instantiate_p__plus__c_plus_p();             //           x0 +     x1
    test_instantiate_c__plus__c_plus_p();             //           x0 +     x1
    test_instantiate_c__plus__p_plus_p();             //           x0 +     x1
    test_instantiate_p_plus_p__plus__p();             //           x1 +     x0
    test_instantiate_p_plus_p__plus__c();             //           x1 +     x0
    test_instantiate_p_plus_c__plus__p();             //           x1 +     x0
    test_instantiate_p_plus_c__plus__c();             //           x1 +     x0
    test_instantiate_c_plus_p__plus__p();             //           x1 +     x0

    test_instantiate_pos_p__plus__p();                //                        x1 +     x0
    test_instantiate_pos_p__plus__c();                //                        x1 +     x0
    test_instantiate_neg_p__plus__p();                //                        x1 +     x0
    test_instantiate_neg_p__plus__c();                //                        x1 +     x0

    test_instantiate_p__plus__Dp();                   // x0 +     D(x0)
    test_instantiate_p__plus__Ip();                   // x0 +     I(x0)

    test_instantiate_Dp__plus__p();                   // D(x0) +  x0
 }

}