#include "polynomial/all_polynomial_tests.h"
#include "monomial/all_monomial_tests.h"
#include "ostream/all_ostream_tests.h"
#include "istream/all_istream_tests.h"
#include "exprs/all_expr_tests.h"
#include "induction/all_induction_tests.h"

using namespace po_test;

void test();

int main()
{
  test();

  // TODO Move to unit test
  PO_ASSERT(po::polynomial::construction_count() == 3287, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2906, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2525, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2370, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2363, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2352, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2277, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2271, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2261, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2246, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2234, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2232, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2233, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2197, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2183, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2182, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2175, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2177, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2168, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2113, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2108, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2237, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2269, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2263, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2260, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2259, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2272, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2320, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2462, po::polynomial::construction_count());
  // PO_ASSERT(po::polynomial::construction_count() == 2455, po::polynomial::construction_count());
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
  all_polynomial_tests();
  all_expr_tests();
  all_induction_tests();
}




