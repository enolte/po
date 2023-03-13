#include "test_instantiate_pos_c__mult__p.h"        //                        x1     * x0
#include "test_instantiate_neg_c__mult__p.h"        //                        x1     * x0
#include "test_instantiate_p__mult__pos_p.h"        //           x0     * x1
#include "test_instantiate_p__mult__neg_p.h"        //           x0     * x1
#include "test_instantiate_c__mult__pos_p.h"        //           x0     * x1
#include "test_instantiate_c__mult__neg_p.h"        //           x0     * x1
#include "test_instantiate_pos_p__mult__p.h"        //                        x1     * x0
#include "test_instantiate_pos_p__mult__c.h"        //                        x1     * x0
#include "test_instantiate_neg_p__mult__p.h"        //                        x1     * x0
#include "test_instantiate_neg_p__mult__c.h"        //                        x1     * x0
#include "test_instantiate_p_mult_c__mult__p.h"     //                        x1     * x0
#include "test_instantiate_p__mult__c_mult_p.h"     //           x0     * x1
#include "test_instantiate_p_mult_p__mult__p.h"     //                        x1     * x0
#include "test_instantiate_p__mult__p_mult_p.h"     //           x0     * x1
#include "test_instantiate_p__mult__p_plus_p.h"     //           x0     * x1
#include "test_instantiate_p__mult__Dp.h"           //           x0     * x1
#include "test_instantiate_p_minus_p__mult__p.h"    //                        x1     * x0

namespace expr_binary_mult_instantiate
{
  void test_instantiate_level_2()
  {
    test_instantiate_pos_c__mult__p();              //                        x1     * x0
    test_instantiate_neg_c__mult__p();              //                        x1     * x0
    test_instantiate_p__mult__pos_p();              //           x0     * x1
    test_instantiate_p__mult__neg_p();              //           x0     * x1
    test_instantiate_c__mult__pos_p();              //           x0     * x1
    test_instantiate_c__mult__neg_p();              //           x0     * x1
    test_instantiate_pos_p__mult__p();              //                        x1     * x0
    test_instantiate_pos_p__mult__c();              //                        x1     * x0
    test_instantiate_neg_p__mult__p();              //                        x1     * x0
    test_instantiate_neg_p__mult__c();              //                        x1     * x0
    test_instantiate_p_mult_c__mult__p();           //                        x1     * x0
    test_instantiate_p__mult__c_mult_p();           //           x0     * x1
    test_instantiate_p_mult_p__mult__p();           //                        x1     * x0
    test_instantiate_p__mult__p_mult_p();           //           x0     * x1
    test_instantiate_p__mult__p_plus_p();           //           x0     * x1
    test_instantiate_p__mult__Dp();                 //           x0     * x1
    test_instantiate_p_minus_p__mult__p();          //                        x1     * x0
  }

}

