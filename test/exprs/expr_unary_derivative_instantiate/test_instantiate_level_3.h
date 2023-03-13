#include "test_instantiate_D__DDc.h"                    // DDD(x0)
#include "test_instantiate_D__DDp.h"                    // DDD(x0)
#include "test_instantiate_D__IDp.h"                    // DID(x0)
#include "test_instantiate_D__IIp.h"                    // DII(x0)

namespace expr_unary_derivative_instantiate
{
  void test_instantiate_level_3()
  {
    test_instantiate_D__DDc();                          // DDD(x0)
    test_instantiate_D__DDp();                          // DDD(x0)
    test_instantiate_D__IDp();                          // DID(x0)
    test_instantiate_D__IIp();                          // DII(x0)
 }

}

