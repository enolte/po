#include "test_tall_QR.h"

namespace po_test
{
  void test_QR()
  {
    test_tall_QR<3, 2>();
    test_tall_QR<3, 3>();
    test_tall_QR<4, 2>();
    test_tall_QR<5, 3>();
    test_tall_QR<8, 8>();
    test_tall_QR<10, 7>();
    test_tall_QR<13, 9>();
    test_tall_QR<18, 5>();
    test_tall_QR<31, 27>();
    // test_tall_QR<71, 18>();
    // test_tall_QR<108, 31>();
    // test_tall_QR<310, 27>();
    // test_tall_QR<254, 100>();
    // test_tall_QR<445, 300>();
    // test_tall_QR<604, 257>();
    // test_tall_QR<708, 231>();
    // test_tall_QR<1000, 497>();
  }

}