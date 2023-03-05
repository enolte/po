#include "../../polynomial.h"

#include "compare.h"

#include <cassert>

#include "test_instantiate_unary_plus_p.h"  // +p
#include "test_instantiate_unary_minus_p.h" // -p

#include "test_instantiate_Dc.h"            // D(x0)
#include "test_instantiate_Dp.h"            // D(x0)

#include "test_instantiate_Ic.h"            // I(x0)
#include "test_instantiate_Ip.h"            // I(x0)

#include "test_instantiate_p_plus_p.h"      // x0 +     x0
#include "test_instantiate_p_plus_c.h"      // x0 +     x0
#include "test_instantiate_c_plus_p.h"      // x0 +     x0
#include "test_instantiate_p_minus_p.h"     // x0   -   x0
#include "test_instantiate_p_minus_c.h"     // x0   -   x0
#include "test_instantiate_c_minus_p.h"     // x0   -   x0
#include "test_instantiate_p_mult_p.h"      // x0     * x0
#include "test_instantiate_p_mult_c.h"      // x0     * x0
#include "test_instantiate_c_mult_p.h"      // x0     * x0


void test_instantiate_level_1()
{
  test_instantiate_unary_plus_p();          // +p
  test_instantiate_unary_minus_p();         // -p

  test_instantiate_Dc();                    // D(x0)
  test_instantiate_Dp();                    // D(x0)

  test_instantiate_Ic();                    // I(x0)
  test_instantiate_Ip();                    // I(x0)

  test_instantiate_p_plus_p();              // x0 +     x0
  test_instantiate_p_plus_c();              // x0 +     x0
  test_instantiate_c_plus_p();              // x0 +     x0
  test_instantiate_p_minus_p();             // x0   -   x0
  test_instantiate_p_minus_c();             // x0   -   x0
  test_instantiate_c_minus_p();             // x0   -   x0
  test_instantiate_p_mult_p();              // x0     * x0
  test_instantiate_p_mult_c();              // x0     * x0
  test_instantiate_c_mult_p();              // x0     * x0

  PO_LINE;
}
