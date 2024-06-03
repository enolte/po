// TODO Rework the comparison test utilities in compare.h
#include <algorithm>
#include <cmath>
#include <valarray>

#include "test_exponents_sequence.h"
#include "test_exponents_sequences.h"
#include "test_vandermonde.h"
#include "test_QR.h"
#include "test_pseudoinverse.h"
#include "test_lagrange_basis.h"
// #include "test_orthonormalization.h"

namespace po_test
{
  void all_induction_tests()
  {
    test_exponents_sequence();
    test_exponents_sequences();
    test_vandermonde();
    test_QR();
    test_pseudoinverse();
    test_lagrange_basis();

    // TODO
    // test_orthonormalization();

    PO_LINE;
  }

}

