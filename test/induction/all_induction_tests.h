// TODO Rework the comparison test utilities in compare.h
#include <algorithm>
#include <cmath>
#include <valarray>

namespace po_test
{
  template<typename T>
  concept numeric = std::is_arithmetic<std::remove_cvref_t<T>>::value;

  bool equal(const std::valarray<double>& xa, std::initializer_list<numeric auto>&& xb)
  {
    return std::ranges::equal(xa, xb);
  }

  bool abs_near(const std::valarray<double>& xa, std::initializer_list<numeric auto>&& xb, double tol = 0x1p-52)
  {
    return std::ranges::equal(xa, xb, [tol](double aa, numeric auto bb) { return std::fabs(aa - bb) <= tol; });
  }
}


#include "test_exponents_sequence.h"
#include "test_exponents_sequences.h"
#include "test_vandermonde.h"
#include "test_QR.h"
#include "test_pseudoinverse.h"
#include "test_lagrange_basis.h"
// #include "test_orthnormalization.h"

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
    // test_orthnormalization();

    PO_LINE;
  }

}

