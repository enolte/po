#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_D__p_plus_p()
{
  // l-values
  {
    po::polynomial p{{1, {3}}}, q{{2, {2}}};
    assert(D(q + p, 0)(-1) == 3 + -4);
  }

  // r-values
  {
    using P = po::polynomial;
    assert(D(P{{-7, {2}}} + P{{1, {3}}}, 0)(1) == -14 + 3);
  }

  PO_LINE;
}