#include "matrix_ostream.h"

#include "../../induction/ls/pseudoinverse.h"
#include "../../induction/ls/vandermonde.h"

#include "pseudoinverse/test_rt_left_pseudoinverse.h"
#include "pseudoinverse/test_full_left_pseudoinverse.h"

#include "pseudoinverse/test_pseudoinverse_rank2_degree1.h"
#include "pseudoinverse/test_pseudoinverse_rank2_degree1_dim2_simplex.h"

#include "pseudoinverse/test_pseudoinverse_rank2_degree2.h"
#include "pseudoinverse/test_pseudoinverse_rank2_degree2_dim2_simplex.h"

namespace po_test
{
  void test_pseudoinverse()
  {
    test_rt_left_pseudoinverse<3, 2>();
    test_rt_left_pseudoinverse<3, 3>();
    test_rt_left_pseudoinverse<4, 2>();
    test_rt_left_pseudoinverse<5, 3>();
    test_rt_left_pseudoinverse<6, 6>();
    test_rt_left_pseudoinverse<8, 8>();
    test_rt_left_pseudoinverse<10, 7>();
    test_rt_left_pseudoinverse<13, 9>();
    test_rt_left_pseudoinverse<18, 5>();
    test_rt_left_pseudoinverse<31, 27>();
    test_rt_left_pseudoinverse<71, 18>();
    test_rt_left_pseudoinverse<108, 31>();
    // test_rt_left_pseudoinverse<310, 27>();
    // test_rt_left_pseudoinverse<254, 100>();
    // test_rt_left_pseudoinverse<445, 300>();
    // test_rt_left_pseudoinverse<604, 257>();
    // test_rt_left_pseudoinverse<708, 231>();
    // test_rt_left_pseudoinverse<1000, 497>();

    test_full_left_pseudoinverse<3, 2>();
    test_full_left_pseudoinverse<3, 3>();
    test_full_left_pseudoinverse<4, 2>();
    test_full_left_pseudoinverse<4, 3>();
    test_full_left_pseudoinverse<6, 6>();
    test_full_left_pseudoinverse<8, 8>();
    test_full_left_pseudoinverse<9, 9>();
    test_full_left_pseudoinverse<10, 7>();
    test_full_left_pseudoinverse<13, 9>();

    test_pseudoinverse_rank2_degree1();
    test_pseudoinverse_rank2_degree1_dim2_simplex();

    test_pseudoinverse_rank2_degree2();
    test_pseudoinverse_rank2_degree2_dim2_simplex();
  }

}