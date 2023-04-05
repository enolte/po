#include "test_instantiate_D__Dc.h"               // D(x1)
#include "test_instantiate_D__Dp.h"               // D(x1)

#include "test_instantiate_D__pos_p.h"            // D(+x0)
#include "test_instantiate_D__neg_p.h"            // D(+x0)

#include "test_instantiate_D__p_plus_p.h"         // D(x0 +     x0)
#include "test_instantiate_D__p_minus_p.h"        // D(x0   -   x0)
#include "test_instantiate_D__p_mult_p.h"         // D(x0     * x0)

#include "test_instantiate_D__Ip.h"               // D(I(x0))
#include "test_instantiate_D__Ap.h"               // D(A(x0))

namespace expr_unary_derivative_instantiate
{
  void test_instantiate_level_2()
  {
    test_instantiate_D__Dc();                     // D(x1)
    test_instantiate_D__Dp();                     // D(x1)

    test_instantiate_D__pos_p();                  // I(+x0)
    test_instantiate_D__neg_p();                  // I(-x0)

    test_instantiate_D__p_plus_p();               // D(x0 +     x0)
    test_instantiate_D__p_minus_p();              // D(x0   -   x0)
    test_instantiate_D__p_mult_p();               // D(x0     * x0)

    test_instantiate_D__Ip();                     // D(I(x0))
    test_instantiate_D__Ap();                     // D(A(x0))
  }

}
