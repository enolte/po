#include "../../polynomial.h"

#include "test_instantiate_neg_p_plus_pos_p.h"        // x1 +     x1
#include "test_instantiate_neg_p_minus_pos_p.h"       // x1   -   x1
#include "test_instantiate_neg_p_mult_pos_p.h"        // x1     * x1

#include "test_instantiate_p_mult_p_mult_p_mult_p.h"  // x0     * x2, x1     * x1, x2     * x0
#include "test_instantiate_p_mult_p_mult_p_plus_p.h"  // x0     * x2, x1     * x1, x2     * x0

#include "test_instantiate_DDDc.h"                    // DDD(x0)
#include "test_instantiate_DDDp.h"                    // DDD(x0)

#include "test_instantiate_DIDp.h"                    // DID(x0)


void test_instantiate_level_3()
{
  test_instantiate_neg_p_plus_pos_p();                // x1 +     x1
  test_instantiate_neg_p_minus_pos_p();               // x1   -   x1
  test_instantiate_neg_p_mult_pos_p();                // x1     * x1

  test_instantiate_p_mult_p_mult_p_mult_p();          // x0     * x2, x1     * x1, x2     * x0
  test_instantiate_p_mult_p_mult_p_plus_p();          // x0     * x2, x1     * x1, x2     * x0

  test_instantiate_DDDc();                            // DDD(x0)
  test_instantiate_DDDp();                            // DDD(x0)

  test_instantiate_DIDp();                            // DID(x0)

  PO_LINE;
}
