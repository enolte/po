// TODO
// #include "test_instantiate_A__c_plus_p.h"       // A(x1)
// #include "test_instantiate_A__p_plus_c.h"       // A(x1)
// #include "test_instantiate_A__p_plus_p.h"       // A(x1)

// #include "test_instantiate_A__c_minus_p.h"      // A(x1)
// #include "test_instantiate_A__p_minus_c.h"      // A(x1)
// #include "test_instantiate_A__p_minus_p.h"      // A(x1)

// #include "test_instantiate_A__c_mult_p.h"       // A(x1)
// #include "test_instantiate_A__p_mult_c.h"       // A(x1)
#include "test_instantiate_A__p_mult_p.h"       // A(x1)

#include "test_instantiate_A__Dp.h"             // A(x1)
#include "test_instantiate_A__Ap.h"             // A(x1)
#include "test_instantiate_A__Ip.h"             // A(x1)
// #include "test_instantiate_A__Dc.h"             // A(x1)
#include "test_instantiate_A__Ac.h"             // A(x1)
// #include "test_instantiate_A__Ic.h"             // A(x1)

// #include "test_instantiate_A__uplus_p.h"        // A(x1)
// #include "test_instantiate_A__uminus_p.h"       // A(x1)

namespace expr_unary_antiderivative_instantiate
{
  void test_instantiate_level_2()
  {
    // test_instantiate_A__c_plus_p();             // A(x1)
    // test_instantiate_A__p_plus_c();             // A(x1)
    // test_instantiate_A__p_plus_p();             // A(x1)

    // test_instantiate_A__c_minus_p();            // A(x1)
    // test_instantiate_A__p_minus_c();            // A(x1)
    // test_instantiate_A__p_minus_p();            // A(x1)

    // test_instantiate_A__c_x_p();                // A(x1)
    // test_instantiate_A__p_x_c();                // A(x1)
    test_instantiate_A__p_mult_p();             // A(x1)

    test_instantiate_A__Dp();                   // A(x1)
    test_instantiate_A__Ap();                   // A(x1)
    test_instantiate_A__Ip();                   // A(x1)
    // test_instantiate_A__Dc();                   // A(x1)
    test_instantiate_A__Ac();                   // A(x1)
    // test_instantiate_A__Ic();                   // A(x1)

    // test_instantiate_A__uplus_p();              // A(x1)
    // test_instantiate_A__uminus_p();             // A(x1)
  }
}

