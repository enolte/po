#include "test_instantiate_p__mult__p_mult_p_mult_p.h"  // x0     * x2
#include "test_instantiate_p_mult_p__mult__p_mult_p.h"  // x1     * x1
#include "test_instantiate_p_mult_p_mult_p__mult__p.h"  // x2     * x0

#include "test_instantiate_p__mult__p_mult_p_plus_p.h"  // x0     * x2
#include "test_instantiate_p_mult_p__mult__p_plus_p.h"  // x1     * x1

#include "test_instantiate_neg_p__mult__pos_p.h"        // x1     * x1

namespace expr_binary_mult_instantiate
{
  void test_instantiate_level_3()
  {
    test_instantiate_p__mult__p_mult_p_mult_p();        // x0     * x2
    test_instantiate_p_mult_p__mult__p_mult_p();        // x1     * x1
    test_instantiate_p_mult_p_mult_p__mult__p();        // x2     * x0

    test_instantiate_p__mult__p_mult_p_plus_p();        // x0     * x2
    test_instantiate_p_mult_p__mult__p_plus_p();        // x1     * x1

    test_instantiate_neg_p__mult__pos_p();              // x1     * x1
  }
}
