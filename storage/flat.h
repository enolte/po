#ifndef PO_STORAGE_FLAT_H
#define PO_STORAGE_FLAT_H

#include "../monomial.h"
#include <vector>

namespace po
{
  inline namespace flat_model
  {
    using storage = std::vector<monomial>;
  }
}

#include "flat/find_coefficient.h"
#include "flat/nterms.h"
#include "flat/constant.h"
#include "flat/accumulate_add.h"
#include "flat/accumulate_mult.h"


#endif

