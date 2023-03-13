#include "test_instantiate_neg_p__plus__pos_p.h"          // x1 +     x1
#include "test_instantiate_Dp_mult_p__plus__p_mult_Dp.h"  // x1 +     x1

namespace expr_binary_plus_instantiate
{
  void test_instantiate_level_3()
  {
    test_instantiate_neg_p__plus__pos_p();                // x1 +     x1
    test_instantiate_Dp_mult_p__plus__p_mult_Dp();        // x1 +     x1
  }

}