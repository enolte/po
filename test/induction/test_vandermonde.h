#include "matrix_ostream.h"

#include "../../induction/ls/vandermonde.h"

#include "vandermonde/test_vandermonde_rank1_degree1.h"
#include "vandermonde/test_vandermonde_rank1_degree2.h"
#include "vandermonde/test_vandermonde_rank1_degree4.h"

#include "vandermonde/test_vandermonde_rank2_degree1.h"
#include "vandermonde/test_vandermonde_rank2_degree2.h"
#include "vandermonde/test_vandermonde_rank2_degree3.h"

#include "vandermonde/test_vandermonde_rank3_degree1.h"
#include "vandermonde/test_vandermonde_rank3_degree2.h"

#include "vandermonde/test_vandermonde_rank2_degree1_dim2_simplex.h"
#include "vandermonde/test_vandermonde_rank2_degree2_dim2_simplex.h"

#include "vandermonde/test_vandermonde_rank3_degree1_dim3_simplex.h"
#include "vandermonde/test_vandermonde_rank3_degree2_dim3_simplex.h"

namespace po_test
{
  void test_vandermonde()
  {
    test_vandermonde_rank1_degree1();
    test_vandermonde_rank1_degree2();
    test_vandermonde_rank1_degree4();

    test_vandermonde_rank2_degree1();
    test_vandermonde_rank2_degree2();
    test_vandermonde_rank2_degree3();

    test_vandermonde_rank3_degree1();
    test_vandermonde_rank3_degree2();

    test_vandermonde_rank2_degree1_dim2_simplex();
    test_vandermonde_rank2_degree2_dim2_simplex();

    test_vandermonde_rank3_degree1_dim3_simplex();
    test_vandermonde_rank3_degree2_dim3_simplex();
  }
}


