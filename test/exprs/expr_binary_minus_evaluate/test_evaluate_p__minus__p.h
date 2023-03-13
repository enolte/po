#include "../../../polynomial.h"
#include "../../macros.h"
#include <cassert>

void test_evaluate_p__minus__p()
{
  {
    po::polynomial p{{9, {1, 1, 0}}, {-.02, {6, 5, 4}}};

    assert((p-p)(3, 2.005, 8) == 0.);
  }

  PO_LINE;
}