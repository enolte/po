#ifndef PO_MONOMIAL_OSTREAM_H
#define PO_MONOMIAL_OSTREAM_H

#include "valarray_ostream.h"

namespace po
{
  template<typename ostream>
  ostream& operator<<(ostream& o, const po::monomial& m)
  {
    // (g++ 11.2.0) This causes a diagnostic re invalid initialization
    // return o << m.coefficient << '[' << m.exponents << ']';
    o << m.coefficient << '[' << m.exponents << ']';
    // o.operator<<(m.coefficient) << '[' << m.exponents << ']';
    return o;
  }
}

#endif


