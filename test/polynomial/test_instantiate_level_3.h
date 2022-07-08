#include "../../polynomial.h"

#include "compare.h"

#include <cassert>

// x2 op x0
// TODO

// x1 + x1
#include "test_instantiate_neg_p_plus_pos_p.h"

// x1 - x1
#include "test_instantiate_neg_p_minus_pos_p.h"

// x1 * x1
#include "test_instantiate_neg_p_mult_pos_p.h"

// x0 op x2
// TODO

// x0 * x2, x1 * x1, x2 * x0
#include "test_instantiate_p_mult_p_mult_p_mult_p.h"
#include "test_instantiate_p_mult_p_mult_p_plus_p.h"

#if 0
// TODO
#include "test_instantiate_pos_p_plus_neg_p.h"
#include "test_instantiate_pos_p_minus_neg_p.h"
#include "test_instantiate_pos_p_mult_neg_p.h"

#endif



void test_instantiate_level_3()
{
  // x1 + x1
  test_instantiate_neg_p_plus_pos_p();
  test_instantiate_neg_p_minus_pos_p();

  // x1 * x1
  test_instantiate_neg_p_mult_pos_p();

  // x0 * x2, x1 * x1, x2 * x0
  test_instantiate_p_mult_p_mult_p_mult_p();
  test_instantiate_p_mult_p_mult_p_plus_p();

  PO_LINE;
}
