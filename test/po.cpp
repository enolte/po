#include "polynomial/all_polynomial_tests.h"
#include "monomial/all_monomial_tests.h"
#include "ostream/all_ostream_tests.h"
#include "istream/all_istream_tests.h"
#include "exprs/all_expr_tests.h"

using namespace po_test;

void test();

int main()
{
  test();

  // TODO Move to unit test
  PO_ASSERT(po::polynomial::construction_count() == 2455, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2451, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2453, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2447, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2453, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2455, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2423, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2401, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2405, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2405, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2401, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2398, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2387, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2499, po::polynomial::construction_count());

  return 0;
}

void test()
{
  all_istream_tests();
  all_ostream_tests();
  all_monomial_tests();
  all_expr_tests();
  all_polynomial_tests();
}




