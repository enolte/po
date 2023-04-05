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




