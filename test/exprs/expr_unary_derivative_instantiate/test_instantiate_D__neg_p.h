#include "../../../ostream/exponents_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_instantiate_D__neg_p()
{
  {
    po::polynomial p{{0, {5, 1}}};
    po::polynomial r = po::instantiate(po::D(-p, 1), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {5, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(-p, 1), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {-2, {5, 0}}, {-6, {2, 1}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(-p, 0), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {-10, {4, 1}}, {-6, {1, 2}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {0, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(-p, 0), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {-10, {4, 1}}, {-6, {1, 2}}, {0, {0, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {7, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(-p, 0), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {-10, {4, 1}}, {-6, {1, 2}}, {0, {0, 0}}
      }),
      r);

    PO_LINE;
  }

  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(-p, 5), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0, 0}}
      }),
      r);

    PO_LINE;
  }

}
