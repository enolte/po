#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_neg_p__minus__c()
{
  // x1 - x0
  {
    po::polynomial p{{6, {0}}};
    po::polynomial r = po::instantiate(-p-8, po::rank<1>{});

    assert(compare::unordered_equal_terms(
      r,
      {
        {-14, {0}}
      }));

    PO_LINE;
  }

}


