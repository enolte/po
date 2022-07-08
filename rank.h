#ifndef PO_RANK_H
#define PO_RANK_H

#include <cstdint>

namespace po
{
  using rank_type = std::size_t;

  template<std::size_t R>
  struct rank
  {
    operator rank_type() && { return R; }
  };
}

#endif


