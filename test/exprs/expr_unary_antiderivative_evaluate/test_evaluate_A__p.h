#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_evaluate_A__p()
{
  // rvalue polynomial, place in range, test 1
  {
    const double x0 = 16;
    const double ex = 384;

    const double ac = po::antiderivative(
      po::polynomial
      {
        { 3, {1, 1}},
      },
      0)(16, 1);

    assert(ac == ex);

    PO_LINE;
  }

  // rvalue polynomial, place in range, test 2
  {

    const double x0 = 3.0058;
    const double ex =
      1.5 * x0*x0 * 4.3 * -4  +
      2 * x0 * -4*-4 +
      -1./3 * x0*x0*x0 * -4*-4*-4*-4;

    const double ac = po::antiderivative(
      po::polynomial
      {
        { 3, {1, 1, 1}},
        { 2, {0, 0, 2}},
        {-1, {2, 0, 4}},
      },
      0)(3.0058, 4.3, -4);

    assert(po_test::near_rel(ac, ex, 0x1p-51));

    PO_LINE;
  }

  // lvalue polynomial, place in range
  {
    const po::polynomial p
    {
      {3, {4, 4, 4, 4, 4, 4, 4, 4, 4}},
      {4, {3, 3, 3, 3, 3, 3, 3, 3, 3}},
      {5, {2, 2, 2, 2, 2, 2, 2, 2, 2}},
      {6, {1, 1, 1, 1, 1, 1, 1, 1, 1}},
    };

    const double ex = 3./5 * 2*2*2*2*2   +   4./4 * 2*2*2*2   +   5./3 * 2*2*2   +   6./2 * 2*2;
    const double ac = po::antiderivative(p, 6)(1, 1, 1, 1, 1, 1, 2, 1, 1);

    PO_ASSERT(near_rel(ac, ex, 0x1.5p-53), rel(ac, ex));

    PO_LINE;
  }

  // lvalue polynomial, place OOR
  {
    po::polynomial p
    {
      { 3, {1, 1, 1}},
      { 2, {0, 0, 2}},
      {-1, {2, 0, 4}},
    };

    const double x0 = 3.0058;
    const double xnew = 2.2;
    const double ex =
       3 * x0 * 4.3 * -4 * xnew +
       2 * -4*-4 * xnew
      -1 * x0*x0 * -4*-4*-4*-4 * xnew;

    const double ac = po::antiderivative(p, 5)(3.0058, 4.3, -4, 1, 1, xnew);

    assert(po_test::near_rel(ac, ex, 0x1p-51));

    PO_LINE;
  }

  // rvalue polynomial, place OOR
  {

    const double x0 = 3.0058;
    const double xnew = 2.2;
    const double ex =
       3 * x0 * 4.3 * -4 * xnew +
       2 * -4*-4 * xnew
      -1 * x0*x0 * -4*-4*-4*-4 * xnew;

    const double ac = po::antiderivative(
      po::polynomial
      {
        { 3, {1, 1, 1}},
        { 2, {0, 0, 2}},
        {-1, {2, 0, 4}},
      },
      5)(3.0058, 4.3, -4, 1, 1, xnew);

    assert(po_test::near_rel(ac, ex, 0x1p-51));

    PO_LINE;
  }

}


