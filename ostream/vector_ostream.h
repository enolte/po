#ifndef PO_VECTOR_OSTREAM_H
#define PO_VECTOR_OSTREAM_H

#include "write.h"

namespace po
{
  template<typename ostream, typename T>
  ostream& operator<<(ostream& o, const std::vector<T>& t)
  {
    return po::write(o, std::cbegin(t), std::cend(t));
  }
}

#endif

