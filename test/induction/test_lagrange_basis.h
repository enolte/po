#include "lagrange/test_lagrange_basis_rank2_degree1.h"
#include "lagrange/test_lagrange_basis_rank2_degree2.h"
#include "lagrange/test_lagrange_basis_rank2_degree3.h"
#include "lagrange/test_lagrange_basis_rank3_degree1.h"
#include "lagrange/test_lagrange_basis_rank3_degree2.h"

#include "lagrange/test_lagrange_basis_rank2_degree1_dim2_simplex.h"
#include "lagrange/test_lagrange_basis_rank2_degree2_dim2_simplex.h"

#include "lagrange/test_lagrange_basis_rank3_degree1_dim2_simplex.h"
#include "lagrange/test_lagrange_basis_rank3_degree2_dim2_simplex.h"
#include "lagrange/test_lagrange_basis_rank3_degree3_dim2_simplex.h"

#include "lagrange/test_lagrange_basis_rank3_degree3_dim3_simplex.h"

#include "lagrange/test_lagrange_basis_rank4_degree5_dim4_simplex.h"
#include "lagrange/test_lagrange_basis_rank4_degree8_dim4_simplex.h"

#include "lagrange/test_lagrange_basis_rank7_degree5_dim4_simplex.h"

namespace po_test
{
  void test_lagrange_basis()
  {
    test_lagrange_basis_rank2_degree1();
    test_lagrange_basis_rank2_degree2();
    test_lagrange_basis_rank2_degree3();

    test_lagrange_basis_rank3_degree1();
    test_lagrange_basis_rank3_degree2();

    test_lagrange_basis_rank2_degree1_dim2_simplex();
    test_lagrange_basis_rank2_degree2_dim2_simplex();

    test_lagrange_basis_rank3_degree1_dim2_simplex();
    test_lagrange_basis_rank3_degree2_dim2_simplex();
    test_lagrange_basis_rank3_degree3_dim2_simplex();

    test_lagrange_basis_rank3_degree3_dim3_simplex();

    test_lagrange_basis_rank4_degree5_dim4_simplex();

    // TODO
    // test_lagrange_basis_rank4_degree8_dim4_simplex();

    test_lagrange_basis_rank7_degree5_dim4_simplex();
  }

}



