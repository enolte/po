#ifndef PO_STORAGE_FLAT_CONSTANT_H
#define PO_STORAGE_FLAT_CONSTANT_H

#include <algorithm>

namespace po
{
  inline namespace flat_model
  {
    static constexpr scalar_type get_constant(const storage& terms)
    {
      scalar_type constant{0};

      std::ranges::for_each(terms,
        [&constant](const auto& t)
        {
          if(t.degree() == 0)
            constant += t.coefficient;
        });

      return constant;
    }
  }
}

#endif

