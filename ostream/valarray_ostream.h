#ifndef PO_VALARRAY_OSTREAM_H
#define PO_VALARRAY_OSTREAM_H

#include "write.h"

namespace po
{
  template<typename ostream, typename T>
  ostream& operator<<(ostream& o, const std::valarray<T>& t)
  {
    return po::write(o, std::cbegin(t), std::cend(t));
  }
}

#endif


