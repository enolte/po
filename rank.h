#ifndef PO_RANK_H
#define PO_RANK_H

#include <cstdint>

namespace po
{
  using rank_type = std::size_t;

  template<rank_type R>
  struct rank
  {
    constexpr operator rank_type() && { return R; }

    // static constexpr rank<R-1> minus_one() { return {}; }
    // static constexpr rank<R+1> plus_one()  { return {}; }
  };
}

#endif


