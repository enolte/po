#include "test_instantiate_I__Ap.h"               // I(A(x0))
#include "test_instantiate_I__Dc.h"               // I(D(x0))
#include "test_instantiate_I__Dp.h"               // I(D(x0))
#include "test_instantiate_I__Ip.h"               // I(I(x0))

#include "test_instantiate_I__neg_p.h"            // I(+x0))
#include "test_instantiate_I__pos_p.h"            // I(-x0))

#include "test_instantiate_I__p_plus_p.h"         // I(x0 +     x0)
#include "test_instantiate_I__p_minus_p.h"        // I(x0   -   x0)
#include "test_instantiate_I__p_mult_p.h"         // I(x0     * x0)

namespace expr_unary_integral_instantiate
{

  void test_instantiate_level_2()
  {
    test_instantiate_I__Ap();                     // I(A(x0))
    test_instantiate_I__Dc();                     // I(D(x0))
    test_instantiate_I__Dp();                     // I(D(x0))
    test_instantiate_I__Ip();                     // I(I(x0))

    test_instantiate_I__pos_p();                  // I(+x0)
    test_instantiate_I__neg_p();                  // I(-x0)

    test_instantiate_I__p_plus_p();               // I(x0 +     x0)
    test_instantiate_I__p_minus_p();              // I(x0   -   x0)
    test_instantiate_I__p_mult_p();               // I(x0     * x0)
  }

}

