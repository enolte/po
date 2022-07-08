#include "../../polynomial.h"

#include "compare.h"

#include <cassert>

#include "test_instantiate_pos_pos_p.h"        // +x1
#include "test_instantiate_pos_neg_p.h"        // +x1
#include "test_instantiate_pos_c_plus_p.h"     // +x1
#include "test_instantiate_pos_c_minus_p.h"    // +x1
#include "test_instantiate_pos_c_mult_p.h"     // +x1
#include "test_instantiate_neg_neg_p.h"        //      -x1
#include "test_instantiate_neg_pos_p.h"        //      -x1
#include "test_instantiate_neg_c_plus_p.h"     //      -x1
#include "test_instantiate_neg_c_minus_p.h"    //      -x1
#include "test_instantiate_neg_c_mult_p.h"     //      -x1
#include "test_instantiate_p_plus_pos_p.h"     //           x0 +     x1
#include "test_instantiate_p_plus_neg_p.h"     //           x0 +     x1
#include "test_instantiate_c_plus_pos_p.h"     //           x0 +     x1
#include "test_instantiate_c_plus_neg_p.h"     //           x0 +     x1
#include "test_instantiate_p_minus_pos_p.h"    //           x0   -   x1
#include "test_instantiate_p_minus_neg_p.h"    //           x0   -   x1
#include "test_instantiate_c_minus_pos_p.h"    //           x0   -   x1
#include "test_instantiate_c_minus_neg_p.h"    //           x0   -   x1
#include "test_instantiate_p_mult_pos_p.h"     //           x0     * x1
#include "test_instantiate_p_mult_neg_p.h"     //           x0     * x1
#include "test_instantiate_c_mult_pos_p.h"     //           x0     * x1
#include "test_instantiate_c_mult_neg_p.h"     //           x0     * x1
#include "test_instantiate_p_plus_p_plus_p.h"  //           x0 +     x1  x1 +     x0
#include "test_instantiate_p_plus_p_plus_c.h"  //           x0 +     x1  x1 +     x0
#include "test_instantiate_p_plus_c_plus_p.h"  //           x0 +     x1  x1 +     x0
#include "test_instantiate_p_plus_c_plus_c.h"  //                        x1 +     x0
#include "test_instantiate_c_plus_c_plus_p.h"  //           x0 +     x1
#include "test_instantiate_pos_p_plus_p.h"     // +x1                    x1 +     x0
#include "test_instantiate_pos_p_plus_c.h"     // +x1                    x1 +     x0
#include "test_instantiate_neg_p_plus_p.h"     //      -x1               x1 +     x0
#include "test_instantiate_neg_p_plus_c.h"     //      -x1               x1 +     x0
#include "test_instantiate_pos_p_minus_p.h"    // +x1                    x1   -   x0
#include "test_instantiate_pos_p_minus_c.h"    // +x1                    x1   -   x0
#include "test_instantiate_neg_p_minus_p.h"    //      -x1               x1   -   x0
#include "test_instantiate_neg_p_minus_c.h"    //      -x1               x1   -   x0
#include "test_instantiate_pos_p_mult_p.h"     // +x1                    x1     * x0
#include "test_instantiate_pos_p_mult_c.h"     // +x1                    x1     * x0
#include "test_instantiate_neg_p_mult_p.h"     //      -x1               x1     * x0
#include "test_instantiate_neg_p_mult_c.h"     //      -x1               x1     * x0
#include "test_instantiate_p_mult_c_mult_p.h"  //           x0     * x1  x1     * x0
#include "test_instantiate_p_mult_p_mult_p.h"  //           x0     * x1  x1     * x0
#include "test_instantiate_p_mult_p_plus_p.h"  //           x0     * x1  x1 +     x0

#if 0
// TODO
#include "test_instantiate_c_plus_p_plus_p.h"  //           x0 +     x1  x1 +     x0
#include "test_instantiate_c_plus_p_plus_c.h"  //           x0 +     x1  x1 +     x0
#include "test_instantiate_p_plus_c_minus_p.h" //           x0 +     x1  x1   -   x0
#include "test_instantiate_c_plus_p_minus_p.h" //           x0 +     x1  x1   -   x0
#include "test_instantiate_c_plus_p_minus_c.h" //           x0 +     x1  x1   -   x0
#include "test_instantiate_c_plus_c_minus_p.h" //           x0 +     x1  x1   -   x0
#include "test_instantiate_p_minus_c_plus_p.h" //           x0   -   x1  x1 +     x0
#include "test_instantiate_c_minus_p_plus_p.h" //           x0   -   x1  x1 +     x0
#include "test_instantiate_c_minus_p_plus_c.h" //           x0   -   x1  x1 +     x0
#include "test_instantiate_c_minus_c_plus_p.h" //           x0   -   x1  x1 +     x0
#include "test_instantiate_p_minus_c_minus_p.h"//           x0   -   x1  x1   -   x0
#include "test_instantiate_c_minus_p_minus_p.h"//           x0   -   x1  x1   -   x0
#include "test_instantiate_c_minus_p_minus_c.h"//           x0   -   x1  x1   -   x0
#include "test_instantiate_c_minus_c_minus_p.h"//           x0   -   x1  x1   -   x0
#include "test_instantiate_p_minus_c_mult_p.h" //           x0   -   x1  x1     * x0
#include "test_instantiate_c_minus_p_mult_p.h" //           x0   -   x1  x1     * x0
#include "test_instantiate_c_minus_p_mult_c.h" //           x0   -   x1  x1     * x0
#include "test_instantiate_c_minus_c_mult_p.h" //           x0   -   x1  x1     * x0
#include "test_instantiate_p_minus_c_plus_p.h" //           x0   -   x1  x1 +     x0
#include "test_instantiate_c_minus_p_plus_p.h" //           x0   -   x1  x1 +     x0
#include "test_instantiate_c_minus_p_plus_c.h" //           x0   -   x1  x1 +     x0
#include "test_instantiate_c_minus_c_plus_p.h" //           x0   -   x1  x1 +     x0
#include "test_instantiate_p_mult_p_mult_c.h"  //           x0     * x1  x1     * x0
#include "test_instantiate_p_mult_c_mult_p.h"  //           x0     * x1  x1     * x0
#include "test_instantiate_p_mult_c_mult_c.h"  //           x0     * x1  x1     * x0
#include "test_instantiate_c_mult_p_mult_p.h"  //           x0     * x1  x1     * x0
#include "test_instantiate_c_mult_p_mult_c.h"  //           x0     * x1  x1     * x0
#include "test_instantiate_c_mult_c_mult_p.h"  //           x0     * x1  x1     * x0
#include "test_instantiate_c_mult_c_mult_c.h"  //           x0     * x1  x1     * x0

#endif

void test_instantiate_level_2()
{
  test_instantiate_pos_pos_p();                // +x1
  test_instantiate_pos_neg_p();                // +x1
  test_instantiate_pos_c_plus_p();             // +x1
  test_instantiate_pos_c_minus_p();            // +x1
  test_instantiate_pos_c_mult_p();             // +x1
  test_instantiate_neg_neg_p();                //      -x1
  test_instantiate_neg_pos_p();                //      -x1
  test_instantiate_neg_c_plus_p();             //      -x1
  test_instantiate_neg_c_minus_p();            //      -x1
  test_instantiate_neg_c_mult_p();             //      -x1
  test_instantiate_p_plus_pos_p();             //           x0 +     x1
  test_instantiate_p_plus_neg_p();             //           x0 +     x1
  test_instantiate_c_plus_pos_p();             //           x0 +     x1
  test_instantiate_c_plus_neg_p();             //           x0 +     x1
  test_instantiate_p_minus_pos_p();            //           x0   -   x1
  test_instantiate_p_minus_neg_p();            //           x0   -   x1
  test_instantiate_c_minus_pos_p();            //           x0   -   x1
  test_instantiate_c_minus_neg_p();            //           x0   -   x1
  test_instantiate_p_mult_pos_p();             //           x0     * x1
  test_instantiate_p_mult_neg_p();             //           x0     * x1
  test_instantiate_c_mult_pos_p();             //           x0     * x1
  test_instantiate_c_mult_neg_p();             //           x0     * x1
  test_instantiate_p_plus_p_plus_p();          //           x0 +     x1  x1 +     x0
  test_instantiate_p_plus_p_plus_c();          //           x0 +     x1  x1 +     x0
  test_instantiate_p_plus_c_plus_p();          //           x0 +     x1  x1 +     x0
  test_instantiate_p_plus_c_plus_c();          //                        x1 +     x0
  test_instantiate_c_plus_c_plus_p();          //           x0 +     x1
  test_instantiate_pos_p_plus_p();             // +x1                    x1 +     x0
  test_instantiate_pos_p_plus_c();             // +x1                    x1 +     x0
  test_instantiate_neg_p_plus_p();             //      -x1               x1 +     x0
  test_instantiate_neg_p_plus_c();             //      -x1               x1 +     x0
  test_instantiate_pos_p_minus_p();            // +x1                    x1   -   x0
  test_instantiate_pos_p_minus_c();            // +x1                    x1   -   x0
  test_instantiate_neg_p_minus_p();            //      -x1               x1   -   x0
  test_instantiate_neg_p_minus_c();            //      -x1               x1   -   x0
  test_instantiate_pos_p_mult_p();             // +x1                    x1     * x0
  test_instantiate_pos_p_mult_c();             // +x1                    x1     * x0
  test_instantiate_neg_p_mult_p();             //      -x1               x1     * x0
  test_instantiate_neg_p_mult_c();             //      -x1               x1     * x0
  test_instantiate_p_mult_c_mult_p();          //           x0     * x1  x1     * x0
  test_instantiate_p_mult_p_mult_p();          //           x0     * x1  x1     * x0
  test_instantiate_p_mult_p_plus_p();          //           x0     * x1  x1 +     x0

  PO_LINE;
}
