/*

Instantiation test cases are separated into levels by number of operators in the
expression to instantiate.

Supported operators are

  op = +, *, -

For specific test cases:

 U  = Not a test case. These expressions represent cases which are covered in
      lower-level test cases. No need to reimplement the C++ expression grammar
      for supported numeric types.

  === Level 0:

    p = `polynomial`
    c = `expr_constant` (scalar)

  === Level 1:

    +x0
                   Done
               _____________

        +p         done
        +c          U

    -x0
                   Done
               _____________

        -p         done
        -c          U

    x0 op x0
                   Done
               _____________

       p + p       done
       p + c       done
       c + p       done
       c + c        U
       p - p       done
       p - c       done
       c - p       done
       c - c        U
       p * p       done
       p * c       done
       c * p       done
       c * c        U


  === Level 2:

    x1 op x0
    x0 op x1

    1 operand:

      +x1
      -x1

                      Done
         _______      _____

          + +p        done
          + -p        done
          - +p        done
          - -p        done

    2 operands:

      [+, -]x0 op x0

      x0 op [+, 1]x0

      [+, -](x0 op x0)


                      Done
       ___________    _____

        +p op  p      + - *
       +(p op  p)     + - *
         p op +p      + - *
        -p op  p      + - *
       -(p op  p)     + - *
         p op -p      + - *
         p op  c      level 1
        +p op  c      + - *
       +(p op  c)     + - *
        -p op  c      + - *
       -(p op  c)     + - *
         c op  p      level 1
       +(c op  p)     + - *
       -(c op  p)     + - *
         c op +p      + - *
         c op -p      + - *
         c op  c        U

    3 operands:

       x0 op x1 = x0 op (x0 op x0)

       x1 op x0 = (x0 op x0) op x0


         x0    x0   x0              Done (3 x 3 table for each expression class in left col)
         _____________      _____________________

         p op (p op p)      + (+)

                            * (+)

         p op (p op c)      + (+)


         p op (c op p)      + (+)

                                            * (*)

         p op (c op c)      level 1
         c op (p op p)
         c op (p op c)
         c op (c op p)      + (+)


         c op (c op c)        U

         (p op p) op p      (+) +

                            (*) +

         (p op p) op c      (+) +


         (p op c) op p      (+) +

                            (*) +           (*) *

         (p op c) op c      (+) +
         (c op p) op p
         (c op p) op c
         (c op c) op p      level 1
         (c op c) op c        U


*/
#include "../../polynomial.h"

#include "test_instantiate_level_1.h"
#include "test_instantiate_level_2.h"
#include "test_instantiate_level_3.h"
#include "test_instantiate_level_4.h"

#if 0
// TODO

#include "test_instantiate_p_plus_m.h"
#include "test_instantiate_p_plus_i.h"
#include "test_instantiate_p_plus_x.h"

#include "test_instantiate_m_plus_p.h"
#include "test_instantiate_m_plus_m.h"
#include "test_instantiate_m_plus_c.h"
#include "test_instantiate_m_plus_i.h"
#include "test_instantiate_m_plus_x.h"

#include "test_instantiate_c_plus_m.h"
#include "test_instantiate_c_plus_i.h"
#include "test_instantiate_c_plus_x.h"

#include "test_instantiate_i_plus_p.h"
#include "test_instantiate_i_plus_m.h"
#include "test_instantiate_i_plus_c.h"
#include "test_instantiate_i_plus_i.h"
#include "test_instantiate_i_plus_x.h"

#include "test_instantiate_x_plus_p.h"
#include "test_instantiate_x_plus_m.h"
#include "test_instantiate_x_plus_c.h"
#include "test_instantiate_x_plus_i.h"
#include "test_instantiate_x_plus_x.h"




#include "test_instantiate_p_minus_m.h"
#include "test_instantiate_p_minus_i.h"
#include "test_instantiate_p_minus_x.h"

#include "test_instantiate_m_minus_p.h"
#include "test_instantiate_m_minus_m.h"
#include "test_instantiate_m_minus_c.h"
#include "test_instantiate_m_minus_i.h"
#include "test_instantiate_m_minus_x.h"

#include "test_instantiate_c_minus_m.h"
#include "test_instantiate_c_minus_i.h"
#include "test_instantiate_c_minus_x.h"

#include "test_instantiate_i_minus_p.h"
#include "test_instantiate_i_minus_m.h"
#include "test_instantiate_i_minus_c.h"
#include "test_instantiate_i_minus_i.h"
#include "test_instantiate_i_minus_x.h"

#include "test_instantiate_x_minus_p.h"
#include "test_instantiate_x_minus_m.h"
#include "test_instantiate_x_minus_c.h"
#include "test_instantiate_x_minus_i.h"
#include "test_instantiate_x_minus_x.h"




#include "test_instantiate_p_mult_m.h"
#include "test_instantiate_p_mult_i.h"
#include "test_instantiate_p_mult_x.h"

#include "test_instantiate_m_mult_p.h"
#include "test_instantiate_m_mult_m.h"
#include "test_instantiate_m_mult_c.h"
#include "test_instantiate_m_mult_i.h"
#include "test_instantiate_m_mult_x.h"

#include "test_instantiate_c_mult_m.h"
#include "test_instantiate_c_mult_i.h"
#include "test_instantiate_c_mult_x.h"

#include "test_instantiate_i_mult_p.h"
#include "test_instantiate_i_mult_m.h"
#include "test_instantiate_i_mult_c.h"
#include "test_instantiate_i_mult_i.h"
#include "test_instantiate_i_mult_x.h"

#include "test_instantiate_x_mult_p.h"
#include "test_instantiate_x_mult_m.h"
#include "test_instantiate_x_mult_c.h"
#include "test_instantiate_x_mult_i.h"
#include "test_instantiate_x_mult_x.h"

#endif

void test_instantiate()
{
  test_instantiate_level_1();
  test_instantiate_level_2();
  test_instantiate_level_3();
  test_instantiate_level_4();

  PO_LINE;
}
