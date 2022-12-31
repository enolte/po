#ifndef PO_MONOMIAL_ISTREAM_H
#define PO_MONOMIAL_ISTREAM_H

#include "exponents_istream.h"

namespace po
{
  template<typename istream>
  istream& operator>>(istream& i, monomial& m)
  {
    char left_bracket, right_bracket;

    i >> m.coefficient >> std::ws
      >> left_bracket >> std::ws
      >> m.exponents >> std::ws
      >> right_bracket >> std::ws;

    return i;
  }


}

#endif



