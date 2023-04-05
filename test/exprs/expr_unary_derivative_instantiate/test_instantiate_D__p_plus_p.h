#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_instantiate_D__p_plus_p()
{
  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {1, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p + q, 0), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {4, 1}}, {6, {1, 2}}, {4, {0, 0}}, {0, {0, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial q{{4, {1, 0}}, {0, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p + q, 0), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {4, 1}}, {6, {1, 2}}, {4, {0, 0}}, {0, {0, 0}}
      }),
      r);

    PO_LINE;
  }

}
